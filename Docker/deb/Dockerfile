FROM debian:stretch


ENV USER test
ENV FFTW_TAR_URL http://www.fftw.org/fftw-3.3.6-pl2.tar.gz
ENV FFTW_TAR fftw-3.3.6-pl2.tar.gz
ENV FFTW_FOLDER fftw-3.3.6-pl2
ENV FFTW_BUILD_FLAGS --enable-threads --with-openmp
ENV GTEST_REPO https://github.com/google/googletest.git

RUN apt-get update
RUN useradd -m -d /home/$USER $USER

RUN apt-get install -y build-essential wget git libhdf5-dev libhdf5-openmpi-dev cmake
RUN cd /home/$USER && git clone https://github.com/s0vereign/Ahti.git \
    && cd Ahti/utils && git clone $GTEST_REPO && wget $FFTW_TAR_URL && tar -xvzf $FFTW_TAR \
    && cd $FFTW_FOLDER && ./configure --prefix=/home/$USER/Ahti/utils/fftw3 $FFTW3_BUILD_FLAGS \
    && make && make install && cd ../.. && mkdir build && cd build &&  cmake .. -Dcustom_FFTW=ON \
    && make
