# Execute this script from your Ahti/build directory

cmake -DDEBUG_BUILD=OFF -Dcustom_FFTW=ON -DTOTEST=OFF ..
make -j 4