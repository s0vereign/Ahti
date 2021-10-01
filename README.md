# Ahti


[![Build Status](https://travis-ci.org/s0vereign/Ahti.svg?branch=dev)](https://travis-ci.org/s0vereign/Ahti)



**A**cellerated

**H**igh Performance Simulation of the 

**T**ime Dependent Schrödinger Equation

**I**n Various environments

## Pre-Installation

### Building an OpenMP enabled FFTW
Ahti requires an OpenMP enabled FFTW. Since this is not the default on most systems, there is a script provided to
automate this process. The given script will install FFTW3 with OpenMP enabled but **no further options** into 
`utils/fftw3`.

To install FFTW3 do

```bash
cd utils
./install_omp_fftw.sh
```

If you wish to achieve further performance gains check out what the architecture you are working on
has available. You can add the `AVX2` and further options found [here](https://www.fftw.org/fftw3_doc/Installation-on-Unix.html) 
by adding the option the here in `install_omp_fftw.sh` 

```bash
./configure --prefix=$PWD/../fftw3 --enable-openmp
```


### Dependencies
Ahti requires the following dependencies:
```
HDF5 
Boost
OpenMP
```


## Building Ahti
Simply execute the following commands
```bash
mkdir build
cd build
cmake .. 
make
```

The cmake options `CUSTOM_FFTW, DEBUG_BUILD, TOTEST` are enabling the test-builds. Debug and testing is disabled by
default and has to be added during the cmake stage. 