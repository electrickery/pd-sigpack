sigpack - signal object library for pure-data (c) 2006 by Martin Weiß

This git-fork of the Pure-data library maxlib is cloned from https://git.puredata.info/cgit/svn2git/libraries/sigpack.git, which is the svn-to-git from https://sourceforge.net/p/pure-data/svn/HEAD/tree/trunk/externals/sigpack/.

The initial changes were adding/recreating some separate directories for source and help files and replace the buildsystem by pd-lib-builder. This to simplify creation of a deken package of the libary.

The sigpack library consists of:
<dl>
 <dt>chop~</dt>       <dd>signal chopping modulator</dd>
 <dt>decimate~</dt>   <dd>signal decimation</dd>
 <dt>diode~</dt>      <dd>diode rectifier network (from swh-plugins diode_1185)</dd>
 <dt>foldback~</dt>   <dd>signal mirror</dd>
 <dt>foldover~</dt>   <dd>foldover distortion (from swh-plugins foldover_1213)</dd>
 <dt>freqdiv~</dt>    <dd>signal frequency divider (from swh-plugins divider_1186)</dd>
 <dt>freqshift~</dt>  <dd>bode frequency shifter (from swh-plugins bode-shifter_1431)</dd>
 <dt>hardlimit~</dt>  <dd>brick hard limiter with residue mixer (from swh-plugins hard_limiter_1413)</dd>
 <dt>harmgen~</dt>    <dd>harmonic generator (from swh-plugins harmonic_gen_1220)</dd>
 <dt>impulse~</dt>    <dd>non-bandlimited single-sample impulses (from swh-plugins impulse_1885)</dd>
 <dt>rectify~</dt>    <dd>flips negative values to positive</dd>
 <dt>round~</dt>      <dd>simple rounder</dd>
 <dt>saturate~</dt>   <dd>soft saturation</dd>
 <dt>shape~</dt>      <dd>reshape input by an exponential function (from swh-plugins shaper_1187)</dd>
 <dt>sieve~</dt>      <dd>simple sample sifter</dd>
 <dt>split~</dt>      <dd>signal split function</dd>
 <dt>transient~</dt>  <dd>transient mangler (from swh-plugins transient_1206)</dd>
 <dt>ustep~</dt>      <dd>signal unity step function</dd>
 <dt>valverect~</dt>  <dd>valve rectifier (from swh-plugins valve_rect_1405)</dd>
 <dt>vowel~</dt>      <dd>simple formant filter</dd>
 <dt>wavewrap~</dt>   <dd>sinus wavewrapper (from swh-plugins sinus_wavewrapper_1198)</dd>
</ul>

See the original README.txt for more information.

For bugs found in this version, please report them to me. Martin is not responsible for bugs introduced by me.

Fred Jan Kraan fjkraan@xs4all.nl 2016-05-05
