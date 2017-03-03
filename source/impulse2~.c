// sigpack
// for
// pure-data
// by weiss
// www.weiss-archiv.de

#include "m_pd.h"
#ifdef _MSC_VER
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#endif

// ------------------------ impulse2~ -----------------------------
// non-bandlimited single-sample impulses
// code from swh_plugins by steve harris www.plugin.org.uk
// maker: Andy Wingo &lt;wingo at pobox dot com&gt;
// copyright: GPL
// name: Nonbandlimited single-sample impulses (Frequency: Control)
// Based on work by James McCartney in SuperCollider.
// This version has the phase inlet reversed, so phase 0 results
// in a pulse at the first sample of the block, not the last.
// Issue reported by Alexandre Torres Porres

static t_class *impulse_tilde_class;

typedef struct _impulse_tilde
{
    t_object x_obj;
	t_sample x_phase;
	t_sample x_sample_rate;
	float x_f;
} t_impulse_tilde;

static void *impulse_tilde_new(t_floatarg f)
{
	t_impulse_tilde *x = (t_impulse_tilde *)pd_new(impulse_tilde_class);
	x->x_f = f;
	x->x_phase = 0.f;
	x->x_sample_rate = sys_getsr();//later put this in impulse_tilde_dsp???
	outlet_new(&x->x_obj, gensym("signal"));
	inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("ft1"));
	return (x);
}

static t_int *impulse_tilde_perform(t_int *w)
{
	t_impulse_tilde *x = (t_impulse_tilde *)(w[1]);
    t_float *in = (t_float *)(w[2]);
    t_float *out = (t_float *)(w[3]);
    int n = (int)(w[4]);
	float frequency, phase_step, value;
    while (n--)
    {
    	frequency = *(in++);
		phase_step = frequency / x->x_sample_rate;
		if (x->x_phase <= 0.f) {
			x->x_phase += 1.f;
			value = 1.f;
		} else {
			value = 0.f;
		} 
	*out++ = value;
	x->x_phase -= phase_step;
    }
    return (w+5);
}

static void impulse_tilde_ft1(t_impulse_tilde *x, t_float phase)
{
	x->x_phase = phase - (int)phase;
}

static void impulse_tilde_dsp(t_impulse_tilde *x, t_signal **sp)
{
    dsp_add(impulse_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void impulse2_tilde_setup(void)
{
    impulse_tilde_class = class_new(gensym("impulse2~"), (t_newmethod)impulse_tilde_new, 0,
    	sizeof(t_impulse_tilde), 0, A_DEFFLOAT, 0);
	CLASS_MAINSIGNALIN(impulse_tilde_class, t_impulse_tilde, x_f);
    class_addmethod(impulse_tilde_class, (t_method)impulse_tilde_dsp, gensym("dsp"), 0);
	class_addmethod(impulse_tilde_class, (t_method)impulse_tilde_ft1, gensym("ft1"), A_FLOAT, 0);
}
