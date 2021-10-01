#!/usr/bin/env bash

NUM_CORES=$(nproc --all)

wget http://www.fftw.org/fftw-3.3.10.tar.gz
tar -xvzf fftw-3.3.10.tar.gz
cd fftw-3.3.10
./configure --prefix=$PWD/../fftw3 --enable-openmp
make -j $NUM_CORES
make install