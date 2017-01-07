#include <iostream>
#include <vector>

// Alpaka for Kernel Acceleration
#include <alpaka/alpaka.hpp>

// MPI
#include <mpi.h>

#include "grid/Globalgrid.h"
#include "grid/Localgrid.h"

int
main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	
	int size;
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	std::cout << size << " " << rank << std::endl;
	MPI_Finalize();
	
	return EXIT_SUCCESS;
}
