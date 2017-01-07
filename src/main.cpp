#include <iostream>
#include <vector>

// GRAYBAT
#include <graybat/Cage.hpp>
#include <graybat/communicationPolicy/BMPI.hpp>
#include <graybat/graphPolicy/BGL.hpp>
#include <graybat/pattern/GridDiagonal.hpp>
#include <graybat/mapping/Consecutive.hpp>

#include <alpaka/alpaka.hpp>

#include "grid/Globalgrid.h"
#include "grid/Localgrid.h"

auto
main()
->int
{
	typedef graybat::communicationPolicy::BMPI   CommunicationPolicy;
	typedef typename CommunicationPolicy::Config config;
	typedef graybat::graphPolicy::BGL <> GraphPolicy;
	typedef graybat::Cage<CommunicationPolicy, GraphPolicy> Cage;
	Cage cage; 
	cage.setGraph(graybat::pattern::GridDiagonal<GraphPolicy>(2,8));
	cage.distribute(graybat::mapping::Consecutive());
	typedef Cage::Vertex Vertex;
	// Iterate over all vertices that I host
	for(Vertex vertex: cage.getHostedVertices()){
    std::cout << vertex.id << std::endl;
	}

	
	return EXIT_SUCCESS;
}
