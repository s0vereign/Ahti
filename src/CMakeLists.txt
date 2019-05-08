############
# Use CMake 3.3.0
############
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)


############
# Change the C Flags
############
option(DEBUG_BUILD "Enables debug macros and disables Optimizations" On)


######
#set(CMAKE_COLOR_MAKEFILE ON)
######
IF(DEBUG_BUILD)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb -O0")
	message(-- Using Debug configuration)
else(DEBUG_BUILD)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
	message("-- Using optimization")
ENDIF(DEBUG_BUILD)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnarrowing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Waddress")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Warray-bounds")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wchar-subscripts")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcomment")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmain")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-braces")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wparentheses")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wreturn-type")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsequence-point")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wtrigraphs")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-function")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-label")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-value")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvolatile-register-var")







############
# Define project
############

PROJECT(ahti)
enable_testing()
include(CTest)

#############
# Add main source file
#############


SET(MAIN_SRC_FILE 				main.cpp
		                        ../include/solvers/StaticCalcs2D.hpp
								../include/containers/Array2D.hpp
								../include/math/CMultFFTW.hpp
								../include/output/SaveGrid2D.hpp
								../include/math/Operators2D.hpp
								../include/math/NormGrid.hpp
								../include/containers/Array3D.hpp
								../include/output/SaveGrid3D.hpp
								../include/math/Operators3D.hpp
                                ../include/solvers/StaticCalcs3D.hpp
                                ../include/solvers/Split_Solver_3D.hpp
								../include/quantumsystems/Harmonicoscillator.hpp
								quantumsystems/Harmonicoscillator.cpp
								quantumsystems/dist-harm-osc.cpp
                                ../include/containers/Array1D.hpp
								../include/math/Operators1D.hpp
								../include/quantumsystems/Hydrogen.hpp
                                quantumsystems/Hydrogen.cpp
                                ../include/math/Factorial.hpp
                                ../include/math/CartToSpherical.hpp)


##############
# Add the Header files to target
##############
file(GLOB HEADER_SRCS "../include/communication/Ring.hpp"
		              "../include/debug/DebugDef.h"
                      "../include/grid/*.hpp"
                      "../include/math/*.hpp"
                      "../include/math/*.h"
                      "../include/solvers/*.hpp")



######
# Add the CMake custom modules
######
LIST(APPEND CMAKE_MODULE_PATH "../utils/cmake")
LIST(APPEND CMAKE_PREFIX_PATH "../utils/fftw3")
###############
# Find Package OpenMPI
###############

FIND_PACKAGE(MPI)
if(MPI_FOUND)
	 set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
	 set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
	 include_directories(${MPI_INCLUDE_PATH})
endif(MPI_FOUND)

############
# Find HDF5
############
set(HDF5_USE_STATIC_LIBRARIES ON)
set(HDF5_FIND_DEBUG ON)
FIND_PACKAGE(HDF5 REQUIRED COMPONENTS HL)
if(HDF5_FOUND)
	include_directories(${HDF5_INCLUDE_DIRS})
endif(HDF5_FOUND)

###########
# Find Boost with Utility Libraries
###########
FIND_PACKAGE(Boost REQUIRED)
if(BOOST_FOUND)
    include_directories(${BOOST_INCLUDE_DIRS})
endif(BOOST_FOUND)

###########
# Find FFTW
###########

option(custom_FFTW "Use a custom FFTW version compiled with --enable-openmp in utils folder" ON)
if(custom_FFTW)
include_directories(${CMAKE_CURRENT_LIST_DIR}/../utils/fftw3/include)

ADD_LIBRARY(libfftw3 STATIC IMPORTED)
SET_PROPERTY(TARGET libfftw3 PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/../utils/fftw3/lib/libfftw3.a)

ADD_LIBRARY(libfftw3_omp STATIC IMPORTED)
SET_PROPERTY(TARGET libfftw3_omp PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/../utils/fftw3/lib/libfftw3_omp.a)

#SET(FFTW_OMP_FLAGS "")

else(custom_FFTW)

FIND_LIBRARY(FFTW REQUIRED)
	message("${FFTW_INCLUDES}")
	include_directories(${FFTW_INCLUDES})
	
	SET(FFTW_OMP_FLAGS "-lfftw3_omp -lfftw3 -lm")
if(APPLE)
	include_directories("/usr/local/Cellar/fftw/3.3.6-pl2/include")
    set(FFTW_OMP_FLAGS "-L/usr/local/Cellar/fftw/3.3.6-pl2/lib ${FFTW_OMP_FLAGS}")
endif()
	message("FFTW LINKS = ${FFTW_LIBRARIES}")
endif(custom_FFTW)



##########
# Find OpenMP
##########
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


############
# User include directories
############
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_LIST_DIR}/../include/")


#########
# Find GoogleTest
#########
include_directories(../utils/googletest/googletest/include)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message(${MAIN_SRC_FILE})
ADD_EXECUTABLE(ahti ${MAIN_SRC_FILE} ${HEADER_SRCS} )
set_target_properties(ahti PROPERTIES
							RUNTIME_OUTPUT_DIRECTORY
							${CMAKE_BINARY_DIR}/bin)
if(custom_FFTW)

TARGET_LINK_LIBRARIES(
    ahti
        ${MPI_LIBRARIES}
        ${HDF5_LIBRARIES}
        ${HDF5_CXX_LIBRARIES}
        ${HDF5_C_LIBRARIES}
        ${FFTW_LIBRARIES}
        ${HDF5_HL_LIBRARIES}
        libfftw3_omp
        libfftw3
)
else(custom_FFTW)
    TARGET_LINK_LIBRARIES(
            ahti
            ${MPI_LIBRARIES}
            ${HDF5_LIBRARIES}
            ${HDF5_CXX_LIBRARIES}
            ${HDF5_C_LIBRARIES}
            ${FFTW_LIBRARIES}
            ${HDF5_HL_LIBRARIES}
            ${FFTW_LIBRARIES}
            ${FFTW_OMP_FLAGS}
    )
endif(custom_FFTW)
option(TOTEST "Enable test build!" OFF)


IF(TOTEST)



    #########
    # Find GoogleTest
    #########
    include_directories(../utils/googletest/googletest/include)

file(GLOB TEST_SRCS ../tests/*.cpp)

foreach(testSrc ${TEST_SRCS})
	get_filename_component(testName ${testSrc} NAME_WE)
	message("-- ${testName} registered!")

endforeach(testSrc)

ADD_EXECUTABLE(runtests ${TEST_SRCS} ../tests/HydrogenTests.cpp ../tests/SphericalTests.cpp)
if(custom_FFTW)
    ###########
    # Find Boost with Utility Libraries
    ###########
    FIND_PACKAGE(Boost REQUIRED)
    if(BOOST_FOUND)
        include_directories(${BOOST_INCLUDE_DIRS})
    endif(BOOST_FOUND)

	TARGET_LINK_LIBRARIES(
			runtests
			${MPI_LIBRARIES}
			${HDF5_LIBRARIES}
			${HDF5_CXX_LIBRARIES}
			${HDF5_C_LIBRARIES}
			${FFTW_LIBRARIES}
			${HDF5_HL_LIBRARIES}
            libfftw3_omp
            libfftw3
			gtest_main
	)
else(custom_FFTW)
    ###########
    # Find Boost with Utility Libraries
    ###########
    FIND_PACKAGE(Boost REQUIRED)
    if(BOOST_FOUND)
        include_directories(${BOOST_INCLUDE_DIRS})
    endif(BOOST_FOUND)

	TARGET_LINK_LIBRARIES(
			runtests
			${MPI_LIBRARIES}
			${HDF5_LIBRARIES}
			${HDF5_CXX_LIBRARIES}
			${HDF5_C_LIBRARIES}
			${FFTW_LIBRARIES}
			${HDF5_HL_LIBRARIES}
			${FFTW_LIBRARIES}
			${FFTW_OMP_FLAGS}
			gtest_main
	)
endif(custom_FFTW)
set_target_properties(runtests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/tests)
add_test(NAME runtests COMMAND ${CMAKE_BINARY_DIR}/tests/runtests)

ENDIF(TOTEST)
