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
								../include/quantumsystems/dist-harm-osc.hpp
								quantumsystems/dist-harm-osc.cpp )



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
FIND_PACKAGE(HDF5 REQUIRED COMPONENTS HL)
if(HDF5_FOUND)
	include_directories(${HDF5_INCLUDE_DIRS})
endif(HDF5_FOUND)


###########
# Find FFTW
###########
FIND_LIBRARY(FFTW3_LIBRARIES NAMES fftw3 libfftw3 PATHS /usr/lib/ REQUIRED)
if(FFTW_FOUND)
	include_directories(${FFTW_INCLUDES})
endif(FFTW_FOUND)



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
ADD_EXECUTABLE(ahti ${MAIN_SRC_FILE} ${HEADER_SRCS})
set_target_properties(ahti PROPERTIES
							RUNTIME_OUTPUT_DIRECTORY
							${CMAKE_BINARY_DIR}/bin)
TARGET_LINK_LIBRARIES(
    ahti
	${MPI_LIBRARIES}
	#${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	${HDF5_LIBRARIES}
	${HDF5_CXX_LIBRARIES}
	${HDF5_C_LIBRARIES}
	${FFTW_LIBRARIES}
	${HDF5_HL_LIBRARIES}
	${FFTW_LIBRARIES}
		${FFTW_OMP_FLAGS}
)

option(TOTEST "Enable test build!" OFF)


IF(TOTEST)

file(GLOB TEST_SRCS ../tests/*.cpp)

foreach(testSrc ${TEST_SRCS})
	get_filename_component(testName ${testSrc} NAME_WE)
	message("-- ${testName} registered!")

endforeach(testSrc)

ADD_EXECUTABLE(runtests ${TEST_SRCS})
target_link_libraries(  runtests
                        ${HDF5_LIBRARIES}
                        ${FFTW_LIBRARIES}
                        ${HDF5_HL_LIBRARIES}
                        gtest_main
        )
set_target_properties(runtests PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/tests)
add_test(NAME runtests COMMAND ${CMAKE_BINARY_DIR}/tests/runtests)

ENDIF(TOTEST)
