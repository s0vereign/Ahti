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

    complex<double> i(0.0,0.0);
    complex<double> j(2.0,1000.0);
    if(rank == 0)
    {   
        
        MPI_Send(&j, 1, MPI::DOUBLE_COMPLEX, 1, 0 , MPI_COMM_WORLD);
    }
    else 
    {
        MPI_Recv(&i, 1, MPI::DOUBLE_COMPLEX, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int ret = 1;
    if (rank == 1 && (i.real() == j.real()) && (i.imag() == j.imag()))
    {
        ret = 0;
        std::cout << "Sending works! i.real="<< i.real() << "i.imag="<< i.imag() << std::endl;
    }

    if(rank == 0)
    {
        MPI_Recv(&ret, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    else 
    {
        MPI_Send(&ret, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return ret;
}