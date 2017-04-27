#pragma once
#include <mpi.h>
#include <stdlib.h>

#include<complex>
#include<vector>
#include<algorithm>
#include<array>

namespace comm{

    int ring_get_next(int rank, int size)
    {
        if(rank == size-1)
        {
            return 0;
        }
        else 
        {
            return rank+1;
        }
    }

    int ring_get_prev(int rank, int size)
    {
        if(rank == 0)
        {
            return size-1;
        }
        else 
        {
            return rank-1;
        }
    }


    
    template<typename T>
    void ring_send(T& send_buffer, int rank, int size, int lgridsize)
    {
        
        int nxt, prv;
        T tmp_send = send_buffer;

        if(size%2==0)
        {
            if(rank%2==0)
            {
                nxt = ring_get_next(rank, size);
                prv  = ring_get_prev(rank, size);
                // MPI::DOUBLE_COMPLEX is wrong, TODO: smart metaprogramming to map
                // C++ type to MPI Type
                MPI_Send(&tmp_send, lgridsize, MPI::DOUBLE_COMPLEX, rank, nxt, 0, MPI_COMM_WORLD);
            }

            if(rank%2!=0)
            {
                nxt = ring_get_next(rank, size);
                prv = ring_get_prev(rank, size);
                
            }
        }
    }

    template<> 
    void ring_send<std::vector<std::complex<double>>>(std::vector<std::complex<double>>& send_buf,
                                                      int rank,
                                                      int size,
                                                      int lgridsize)
    {
        using std::complex;
        using std::array;
        using std::vector;

        vector<complex<double>> tmp_recv(lgridsize);
        

        int nxt, prv;

        if(size%2 == 0)
        {
            if(rank%2==0)
            {
                nxt = ring_get_next(rank, size);
                prv  = ring_get_prev(rank, size);
                MPI_Send(send_buf.data(), lgridsize, MPI::DOUBLE_COMPLEX, nxt, 0, MPI_COMM_WORLD);
                MPI_Recv(tmp_recv.data(), lgridsize, MPI::DOUBLE_COMPLEX, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            if(rank%2!=0)
            {
                nxt = ring_get_next(rank, size);
                prv = ring_get_prev(rank, size);
                
                MPI_Recv(tmp_recv.data(), lgridsize, MPI::DOUBLE_COMPLEX, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(send_buf.data(), lgridsize, MPI::DOUBLE_COMPLEX, nxt, 0, MPI_COMM_WORLD);
            }
        }
        else 
        {
            nxt = ring_get_next(rank, size);
            prv = ring_get_prev(rank, size);

            if(rank == size-1)
            {
                MPI_Recv(tmp_recv.data(), lgridsize, MPI::DOUBLE_COMPLEX, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(send_buf.data(), lgridsize, MPI::DOUBLE_COMPLEX, nxt, 0, MPI_COMM_WORLD);
            }

            if(rank == 0)
            {
                
                MPI_Send(send_buf.data(), lgridsize, MPI::DOUBLE_COMPLEX, nxt, 0, MPI_COMM_WORLD);
                MPI_Recv(tmp_recv.data(), lgridsize, MPI::DOUBLE_COMPLEX, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }

            if(rank%2==0 && (rank!=0&&rank!=size-1))
            {
                MPI_Recv(tmp_recv.data(), lgridsize, MPI::DOUBLE_COMPLEX, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Send(send_buf.data(), lgridsize, MPI::DOUBLE_COMPLEX, nxt, 0, MPI_COMM_WORLD);
                
            }

            if(rank%2!=0 && (rank!=0&&rank!=size-1))
            {   
                MPI_Send(send_buf.data(), lgridsize, MPI::DOUBLE_COMPLEX, nxt, 0, MPI_COMM_WORLD);
                MPI_Recv(tmp_recv.data(), lgridsize, MPI::DOUBLE_COMPLEX, prv, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        auto recv_it = std::begin(tmp_recv);
        std::copy(send_buf.begin(), send_buf.end(), recv_it);
        
    }
} //COMM
