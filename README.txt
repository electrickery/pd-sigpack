sigpack version 0.04

signal object library for pure-data

objects:
chop~ decimate~ diode~ foldback~ foldover~ freqdiv~
freqshift~ hardlimit~ harmgen~ impulse~ rectify~ round~ saturate~ shape~ sieve~
split~ transient~ ustep~ valverect~ vowel~ wavewrap~


these are based on code from swh_plugins (http://plugin.org.uk):
diode~.c foldover~.c freqdiv~.c freqshift~.c hardlimit~.c harmgen~.c impulse~.c
shape~.c transient~.c valverect~.c wavewrap~.c


released under the GNU/GPL-license
this is software with absolutely no warranty
use it at your own risk

contact
<postmeister@weiss-archiv.de>
<http://www.weiss-archiv.de>


-----------------TODO--------------------
:: update swh_plugins code from latest release: http://plugin.org.uk/releases/0.4.15

-----------------v0.46.0------------------
Completed transition of Makefile.pd-lib-builder location.

-----------------v0.45.1------------------
::changed version format to conform to standard practice. As there are no finctional changes, this counts as bugfix.
::updated the Makefile.pd-lib-builder to 0.6.0.
::updated email address.

-----------------v0.0.45------------------
::normalized version to major.minor.bugfix
::made Makefile more future proof
::added objects.txt for object search in Find Externals... (deken plugin)

-----------------v0.044------------------
::decimate~: fixed gitch at block start
::freqshift~: fixed off-by-one loop causing NaNs. (Partially) updated from upstream
::round~: fixed division by zero issue
::transient~: optimized/updated
::vowel~: moved static array to instance struct to allow multiple instances and prevent NaNs
::*-help.pd: reformatted and improved

-----------------v0.043------------------
:: removed type-punning since it doesn't work for 64-bit or C99

-----------------v0.042------------------
::removed "sp_" prefix from object names

-----------------v0.04-------------------
::cleaning up code a bit
::add GNU/GPL license.txt
::new objects:
  sp_hardlimit~ sp_impulse~ sp_shape~ sp_transient~ sp_valverect~ sp_wavewrap~

-----------------v0.03b------------------
::change prefix to "sp_", so every extern compiles as single object (for pd-extended)

-----------------v0.03-------------------
::add prefix "sp." to avoid nameclash
::new objects:
  sp_diode~ sp_freqshift~ sp_round~ sp_sieve~

-----------------v0.02-------------------
::new objects:
  sp_chop~ sp_decimate~ sp_foldover~ sp_freqdiv~ sp_harmgen~ sp_saturate~ sp_vowel~
  
-----------------v0.01-------------------
::initial release
