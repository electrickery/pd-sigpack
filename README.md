sigpack - signal object library for pure-data (c) 2006 by Martin Weiß

This git-fork of the Pure-data library maxlib is cloned from https://git.puredata.info/cgit/svn2git/libraries/sigpack.git, which is the svn-to-git from https://sourceforge.net/p/pure-data/svn/HEAD/tree/trunk/externals/sigpack/.

The initial changes were adding/recreating some separate directories for source and help files and replace the buildsystem by pd-lib-builder. This to simplify creation of a deken package of the libary.

A subset of the objects is derived from the swh_plugins written by Steve Harris (http://www.plugin.org.uk):
<ul>
 <li>diode~     (diode_1185)
 <li>foldover~  (foldover_1213)
 <li>freqdiv~   (divider_1186)
 <li>freqshift~ (bode-shifter_1431)
 <li>hardlimit~ (hard_limiter_1413)
 <li>harmgen~   (harmonic_gen_1220)
 <li>impulse~   (impulse_1885)
 <li>shape~     (shaper_1187)
 <li>transient~ (transient_1206)
 <li>valverect~ (valve_rect_1405)
 <li>wavewrap~  (sinus_wavewrapper_1198)
</ul>

See the original README.txt for more information.

For bugs found in this version, please report them to me. Martin is not responsible for bugs introduced by me.

Fred Jan Kraan fjkraan@xs4all.nl 2016-04-09
