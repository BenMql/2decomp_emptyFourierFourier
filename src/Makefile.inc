# Configurations on an ordinary Linux PC for Coral
# =================================================


# Platform-dependent information - fftw path:
#============================================

FFTW_PATH=${HOME}/software/fftw/fftw-3.3.9



#
#
# In all likelyhood, the path to fftw3 is the only tweak needed in this
# file. Coral user probably do not need venturing further in this file.
#
#





# 2DECOMP&FFT options
#====================

OPTIONS=-DDOUBLE_PREC
FFT=fftw3_f03

INC=-I$(FFTW_PATH)/include

ifneq (,$(findstring DGLOBAL_ARRAYS,$(OPTIONS)))
  GA_PATH=/opt/ga-5-0-2
  INC+= -I$(GA_PATH)/include
endif

ifneq (,$(findstring DT3PIO,$(OPTIONS)))
  T3PIO_PATH=/opt/t3pio
  INC+= -I$(T3PIO_PATH)/include
endif


#----------------------- Fortran Compiler ----------------------------
F90=mpif90

# enable preprocessing
CPPFLAGS=-cpp
# enable Cray pointer support if needed
CRAYPTR=-fcray-pointer
# optimisation or debugging flags
#OPTIM=-g -fcheck=all
OPTIM=-O2

F90FLAGS=$(OPTIM) $(CRAYPTR) $(CPPFLAGS) $(INC)
LDFLAGS=$(OPTIM)

#--------------------------C Compiler---------------------------------
CC=mpicc
CFLAGS=-O3

#-----------------------External Library------------------------------

# For FFTW
LIB_FFTW3=-L$(FFTW_PATH)/lib -lfftw3f -lfftw3
LIBFFT=$(LIB_FFTW3)

