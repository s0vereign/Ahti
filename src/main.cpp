#include <iostream>
#include <vector>

// GRAYBAT
#include <graybat/Cage.hpp>
#include <graybat/communicationPolicy/ZMQ.hpp>
#include <graybat/graphPolicy/BGL.hpp>
#include <graybat/pattern/GridDiagonal.hpp>
#include <graybat/mapping/Consecutive.hpp>
#include <graybat/pattern/HyperCube.hpp>

// Alpaka for Kernel Acceleration
#include <alpaka/alpaka.hpp>

#include "grid/Globalgrid.h"
#include "grid/Localgrid.h"

auto
main()
->int
{
	typedef graybat::communicationPolicy::ZMQ   CommunicationPolicy;
	typedef typename CommunicationPolicy::Config Config;
	typedef graybat::graphPolicy::BGL <> GraphPolicy;
	typedef graybat::Cage<CommunicationPolicy, GraphPolicy> Cage;
	Config config;
	Cage cage(config); 
	cage.setGraph(graybat::pattern::GridDiagonal<GraphPolicy>(4,1));
	cage.distribute(graybat::mapping::Consecutive());
	typedef Cage::Vertex Vertex;
	// Iterate over all vertices that I host
	typedef Cage::Edge Edge;
	for(Vertex vertex: cage.getHostedVertices()){
    for(Edge outEdge : cage.getOutEdges(vertex)){
        Vertex sourceVertex = outEdge.source;
        Vertex targetVertex = outEdge.target;
        std::cout << "From vertex " << sourceVertex.id
                  << " over edge "   << outEdge.id
                  << " to vertex "   << targetVertex.id << std::endl;
    }
	}
	

	
	
	return EXIT_SUCCESS;
}
