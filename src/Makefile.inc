# Configurations on an ordinary Linux PC for Coral
# =================================================


# Platform-dependent information - fftw path:
#============================================

FFTW_PATH=${HOME}/software/fftw-3.3.8



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
OPTIM=-O3

F90FLAGS=$(OPTIM) $(CRAYPTR) $(CPPFLAGS) $(INC)
LDFLAGS=$(OPTIM)

#--------------------------C Compiler---------------------------------
CC=mpicc
CFLAGS=-O3

#-----------------------External Library------------------------------

# For FFTW
LIB_FFTW3=-L$(FFTW_PATH)/lib -lfftw3f -lfftw3

# For ACML
# This assumes that 32-bit ACML installed at /opt/. Adjust properly.
# It helps to create a symbolic link such as 'acml -> acml4.4.0'
# and update the symbolic link when future ACML version is installed. 
LIB_ACML=/opt/acml/gfortran32/lib/libacml.a -lrt

# For FFTPACK5 
FFTPACK5_PATH=$(HOME)/software/fftpack5
LIB_FFTPACK5=$(FFTPACK5_PATH)/libfftpack5.a

# For Intel MKL
MKL_LIB_PATH= $(MKL_PATH)/lib/ia32
LIB_MKL=-Wl,--start-group $(MKL_LIB_PATH)/libmkl_gf.a $(MKL_LIB_PATH)/libmkl_sequential.a $(MKL_LIB_PATH)/libmkl_core.a -Wl,--end-group -lpthread

# For FFTE
FFTE_PATH=$(HOME)/software/ffte-4.1
LIB_FFTE=$(FFTE_PATH)/libffte.a

ifeq ($(FFT),generic)
     LIBFFT=
else ifeq ($(FFT),acml)
     LIBFFT=$(LIB_ACML)
else ifeq ($(FFT),ffte)
     LIBFFT=$(LIB_FFTE)
else ifeq ($(FFT),fftpack5)
     LIBFFT=$(LIB_FFTPACK5)
else ifeq ($(FFT),fftw3)
     LIBFFT=$(LIB_FFTW3)
else ifeq ($(FFT),fftw3_f03)
     LIBFFT=$(LIB_FFTW3)
else ifeq ($(FFT),mkl)
     LIBFFT=$(LIB_MKL)
endif	
