############
# Use CMake 3.3.0
############

CMAKE_MINIMUM_REQUIRED(VERSION 3.3.0)


############
# Change the C Flags
############

######
#set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-compare")
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


#############
# Add main source file
#############

SET(MAIN_SRC_FILE "main.cpp")


#-------------------------------------------------------------------------------
# Find alpaka.
#-------------------------------------------------------------------------------

SET(ALPAKA_ROOT "${CMAKE_CURRENT_LIST_DIR}/../utils/alpaka/" CACHE STRING "The location of the alpaka library")
LIST(APPEND CMAKE_MODULE_PATH "${ALPAKA_ROOT}")
FIND_PACKAGE("alpaka" REQUIRED)
if(ALPAKA_FOUND)
message("-- alapaka detected")
endif(ALPAKA_FOUND)

INCLUDE_DIRECTORIES(${alpaka_INCLUDE_DIRS})


INCLUDE("${ALPAKA_ROOT}cmake/common.cmake")
INCLUDE("${ALPAKA_ROOT}cmake/dev.cmake")



###############
# Find Package OpenMPI
###############

FIND_PACKAGE(MPI)
if(MPI_FOUND)
	 set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
	 set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
	 include_directories(${MPI_INCLUDE_PATH})
endif(MPI_FOUND)


#############
# Include directory
#############
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_LIST_DIR}/../include/")

##############
# Find Boost
##############
FIND_PACKAGE(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(Boost_INCLUDE_DIRS)

#############
# Add executable
#############
#LIST(REMOVE_DUPLICATES CUDA_NVCC_FLAGS)
#STRING(REPLACE "-arch=sm_20" "" CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS})
#message("${CUDA_NVCC_FLAGS}")

IF(CUDA_FOUND)
STRING(REPLACE "-std=c++11" " " CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
ELSE(CUDA_FOUND)
STRING(REPLACE "14" "11" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
ENDIF(CUDA_FOUND)
message(${CMAKE_CXX_FLAGS})
#message(${CUDA_NVCC_FLAGS})

ALPAKA_ADD_EXECUTABLE(ahti ${MAIN_SRC_FILE})
TARGET_LINK_LIBRARIES(
    ahti
	PUBLIC "alpaka"
	${MPI_LIBRARIES}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

option(TOTEST "Enable test build!" OFF)


IF(TOTEST)


enable_testing()

file(GLOB TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/../include/tests/*.cpp)

foreach(testSrc ${TEST_SRCS})

  get_filename_component(testName ${testSrc} NAME_WE)
	
	ALPAKA_ADD_EXECUTABLE(${testName} ${testSrc})
	target_link_libraries(${testName}
												PUBLIC "alpaka"
												${MPI_LIBRARIES}
												${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
												)
	set_target_properties(${testName} PROPERTIES
																RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/testBin)
	add_test(NAME ${testName}
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/testBin
COMMAND ${CMAKE_CURRENT_BINARY_DIR}/testBin/${testName})
endforeach(testSrc)
ENDIF()
