############
# Use CMake 3.3.0
############
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)


############
# Change the C Flags
############
option(DEBUG_BUILD "Enables debug macros and disables Optimizations" ON)

######
#set(CMAKE_COLOR_MAKEFILE ON)
######
IF(DEBUG_BUILD)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb")
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


SET(MAIN_SRC_FILE "main.cpp")
file(GLOB HEADER_SRCS "*.hpp")


##########
# Build the include 
##########


#-------------------------------------------------------------------------------
# Find alpaka.
#-------------------------------------------------------------------------------

#SET(ALPAKA_ROOT "${CMAKE_CURRENT_LIST_DIR}/../utils/alpaka/" CACHE STRING "The location of the alpaka library")
#LIST(APPEND CMAKE_MODULE_PATH "${ALPAKA_ROOT}")
#FIND_PACKAGE("alpaka")
#if(ALPAKA_FOUND)
#message("-- alapaka detected")
#endif(ALPAKA_FOUND)

#INCLUDE_DIRECTORIES(${alpaka_INCLUDE_DIRS})


#INCLUDE("${ALPAKA_ROOT}cmake/common.cmake")
#INCLUDE("${ALPAKA_ROOT}cmake/dev.cmake")

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
FIND_PACKAGE(FFTW REQUIRED)
if(FFTW_FOUND)
	include_directories(${FFTW_INCLUDES})
endif(FFTW_FOUND)



##########
# Find OpenMP
##########
find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

##########
# Find libsplash (Used later maybe!)
##########
#set(CMAKE_MODULE_PATH  ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../utils/cmake)

#set(Splash_USE_STATIC_LIBS ON)
#find_package(Splash)

#if(Splash_FOUND)
#    include_directories(${Splash_INCLUDE_DIRS})
#    set(LIBS ${LIBS} ${Splash_LIBRARIES})
#endif(Splash_FOUND)

############
# User include directories
############
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_LIST_DIR}/../include/")

##############
# Find Boost
##############
FIND_PACKAGE(Boost REQUIRED unit_test_framework)
if(Boost_FOUND)
	message(Boost_INCLUDE_DIRS)
	include_directories(${Boost_INCLUDE_DIRS})
	ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

endif(Boost_FOUND)

#############
# Add executable
#############
#LIST(REMOVE_DUPLICATES CUDA_NVCC_FLAGS)
#STRING(REPLACE "-arch=sm_20" "" CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS})
#message("${CUDA_NVCC_FLAGS}")



#IF(CUDA_FOUND)
#message("${CUDA_NVCC_FLAGS}")
#message("${CMAKE_CXX_FLAGS}")
#STRING(REPLACE "-std=c++11" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
#message("Current flags: ")
#message("${CUDA_NVCC_FLAGS}")
#message("${CMAKE_CXX_FLAGS}")

#ELSE(CUDA_FOUND)
#STRING(REPLACE "14" "11" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
#ENDIF(CUDA_FOUND)

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
	${FFTW_LIBRARIES}
	${HDF5_HL_LIBRARIES}
	${FFTW_LIBRARIES}
)

option(TOTEST "Enable test build!" OFF)


IF(TOTEST)

file(GLOB TEST_SRCS ../tests/*.cpp)

foreach(testSrc ${TEST_SRCS})

	get_filename_component(testName ${testSrc} NAME_WE)
	message("${testName}")
	ADD_EXECUTABLE(${testName} ${testSrc})
	target_link_libraries(  ${testName}
							${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
							${MPI_LIBRARIES}
						 )
	set_target_properties(${testName} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/tests)
	add_test(NAME ${testName} COMMAND ${CMAKE_BINARY_DIR}/tests/${testName})
endforeach(testSrc)

ENDIF(TOTEST)
