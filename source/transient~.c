// sigpack
// for
// pure-data
// by weiss
// www.weiss-archiv.de

#include "m_pd.h"
#include <math.h>
#include <string.h>
#ifdef _MSC_VER
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )
#endif
#define BUFFER_SIZE 10240
#define SSTAB 0.00001f
#define ASTAB 0.02f
//Truncate-to-zero modulo (ANSI C doesn`t specify) will only work
//if -m < v < 2m
#define MOD(v,m) (v < 0 ? v+m : (v >= m ? v-m : v))

// ------------------------ transient~ ----------------------------- 
// transient mangler
// code from swh_plugins by steve harris www.plugin.org.uk  

static t_class *transient_tilde_class;

typedef struct _transient_tilde
{
    t_object x_obj;
	t_sample x_attack;//-1 - 1
	t_sample x_sustain;//-1 - 1
	t_float *x_buffer;
	int x_buffer_pos;
	long x_count;
	t_float x_fast_buffer_sum;
	t_float x_fast_track;
	t_float x_medi_buffer_sum;
	t_float x_medi_track;
	int x_sample_rate;
	t_float x_slow_buffer_sum;
	t_float x_slow_track;
	t_float x_f;
} t_transient_tilde;

static void *transient_tilde_new(t_floatarg attack, t_floatarg sustain)
{
    t_transient_tilde *x = (t_transient_tilde *)pd_new(transient_tilde_class);
	x->x_attack = attack;
	x->x_sustain = sustain;
    outlet_new(&x->x_obj, gensym("signal"));
	floatinlet_new(&x->x_obj, &x->x_attack);
	floatinlet_new(&x->x_obj, &x->x_sustain);
	//memset(x->x_buffer, '/0', BUFFER_SIZE * sizeof(float));
	x->x_buffer = getbytes(BUFFER_SIZE * sizeof(float));
	x->x_fast_buffer_sum = 0.1;
	x->x_medi_buffer_sum = 0.1;
	x->x_slow_buffer_sum = 0.1;
	x->x_buffer_pos = 0;
	x->x_fast_track = 0.0;
	x->x_medi_track = 0.0;
	x->x_slow_track = 0.0;
	x->x_count = 0;
	x->x_sample_rate = sys_getsr();
	x->x_f = 0;
	if (attack) x->x_attack = attack;
	else x->x_attack = 0.0;
	if (sustain) x->x_sustain = sustain;
	else x->x_sustain = 0.0;
    return (x);
}

static t_int *transient_tilde_perform(t_int *w)
{
	t_transient_tilde *x = (t_transient_tilde *)(w[1]);
    t_float *inVal = (t_float *)(w[2]);
    t_float *outVal = (t_float *)(w[3]);
    int n = (int)(w[4]);
	const int fast_sum_size = (2 * x->x_sample_rate) / 1000;
	const int medi_sum_size = (25 * x->x_sample_rate) / 1000;
	const int slow_sum_size = (100 * x->x_sample_rate) / 1000;
	const float fast_track_lag = 1.5f / fast_sum_size;
	const float medi_track_lag = 1.0f / medi_sum_size;
	const float slow_track_lag = 1.3f / slow_sum_size;
	t_float ratio;
    
	t_float attack          = x->x_attack;
	t_float sustain         = x->x_sustain;
    t_float *buffer         = x->x_buffer;
 	int buffer_pos          = x->x_buffer_pos;
	long count              = x->x_count;
	t_float fast_buffer_sum = x->x_fast_buffer_sum;
	t_float fast_track      = x->x_fast_track;
	t_float medi_buffer_sum = x->x_medi_buffer_sum;
	t_float medi_track      = x->x_medi_track;
	t_float slow_buffer_sum = x->x_slow_buffer_sum;
	t_float slow_track      = x->x_slow_track;
    t_float in;

    while (n--)
    {
		in = *inVal++;
        buffer[buffer_pos] = fabs(in);
        fast_buffer_sum += buffer[buffer_pos];
        medi_buffer_sum += buffer[buffer_pos];
        slow_buffer_sum += buffer[buffer_pos];
        fast_buffer_sum -= buffer[MOD(buffer_pos - fast_sum_size, BUFFER_SIZE)];
        medi_buffer_sum -= buffer[MOD(buffer_pos - medi_sum_size, BUFFER_SIZE)];
        slow_buffer_sum -= buffer[MOD(buffer_pos - slow_sum_size, BUFFER_SIZE)];
        if (count++ > slow_sum_size) {
                fast_track += (fast_buffer_sum/fast_sum_size - fast_track)
                 * fast_track_lag;
                medi_track += (medi_buffer_sum/medi_sum_size - medi_track)
                 * medi_track_lag;
                slow_track += (slow_buffer_sum/slow_sum_size - slow_track)
                 * slow_track_lag;
        }

        // Attack
        ratio = (fast_track + ASTAB) / (medi_track + ASTAB);
        if (ratio * attack > 1.0f) {
                in *= ratio * attack;
        } else if (ratio * attack < -1.0f) {
                in /= ratio * -attack;
        }

        // Sustain
        ratio = (slow_track + SSTAB) / (medi_track + SSTAB);
        if (ratio * sustain > 1.0f) {
                in *= ratio * sustain;
        } else if (ratio * sustain < -1.0f) {
                in /= ratio * -sustain;
        }
		*outVal++ = in;
		buffer_pos = (buffer_pos + 1) % BUFFER_SIZE;
    }
    x->x_buffer_pos      = buffer_pos;
    x->x_count           = count;
    x->x_fast_buffer_sum = fast_buffer_sum;
    x->x_fast_track      = fast_track;
    x->x_medi_buffer_sum = medi_buffer_sum;
    x->x_medi_track      = medi_track;
    x->x_slow_buffer_sum = slow_buffer_sum;
    x->x_slow_track      = slow_track;
    
    return (w+5);
}

static void transient_tilde_dsp(t_transient_tilde *x, t_signal **sp)
{
    dsp_add(transient_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void transient_tilde_setup(void)
{
    transient_tilde_class = class_new(gensym("transient~"), (t_newmethod)transient_tilde_new, 0,
    	sizeof(t_transient_tilde), 0, A_DEFFLOAT, A_DEFFLOAT, 0);
    CLASS_MAINSIGNALIN(transient_tilde_class, t_transient_tilde, x_f);
    class_addmethod(transient_tilde_class, (t_method)transient_tilde_dsp, gensym("dsp"), 0);
}
