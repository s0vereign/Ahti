#pragma once
#include <mpi.h>
#include <stdlib.h>

#include<complex>
#include<vector>
#include<algorithm>
#include<array>

namespace comm
{
    template<typename T>
    void ring_send(T& send_buffer, int rank, int size, int lgridsize);

    int ring_get_prev(int rank, int size);
    int ring_get_next(int rank, int size);


} //COMM
