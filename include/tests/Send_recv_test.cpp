#include <complex>
#include <mpi.h>
#include <iostream>


int main(int argc, char** argv)
{
    using std::complex;
    int size;
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);


    int ret = 0;
    int q[size];

    int sender = rank+10;
    MPI_Gather(&sender, 1, MPI_INT, &q, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        for(int i = 0; i < size ; i++)
        {
            std::cout << q[i] << std::endl;
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return ret;
}