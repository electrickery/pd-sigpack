# Makefile for Makefile.pdlibbuilder. 

lib.name := sigpack
 
chop~.class.sources =      source/chop~.c  
decimate~.class.sources =  source/decimate~.c  
diode~.class.sources =     source/diode~.c  
foldback~.class.sources =  source/foldback~.c  
foldover~.class.sources =  source/foldover~.c  
freqdiv~.class.sources =   source/freqdiv~.c  
freqshift~.class.sources = source/freqshift~.c  
hardlimit~.class.sources = source/hardlimit~.c  
harmgen~.class.sources =   source/harmgen~.c  
impulse~.class.sources =   source/impulse~.c  
rectify~.class.sources =   source/rectify~.c  
round~.class.sources =     source/round~.c  
saturate~.class.sources =  source/saturate~.c  
shape~.class.sources =     source/shape~.c  
sieve~.class.sources =     source/sieve~.c  
split~.class.sources =     source/split~.c  
transient~.class.sources = source/transient~.c  
ustep~.class.sources =     source/ustep~.c  
valverect~.class.sources = source/valverect~.c  
vowel~.class.sources =     source/vowel~.c  
wavewrap~.class.sources =  source/wavewrap~.c

datafiles = \
$(wildcard help/*-help.pd) \
LICENSE.txt \
README.txt \
sigpack-meta.pd

externalsdir = ..
# include Makefile.pdlibbuilder from parent or current directory 
-include $(externalsdir)/Makefile.pdlibbuilder 

ifndef Makefile.pdlibbuilder 
include Makefile.pdlibbuilder 
endif

