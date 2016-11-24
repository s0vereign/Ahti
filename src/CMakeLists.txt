############
# Use CMake 3.3.0
############

CMAKE_MINIMUM_REQUIRED(VERSION 3.3.0)


############
# Change the C Flags
############

######
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
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
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-function")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-label")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-value")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-variable")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvolatile-register-var")









############
# Define project
############

PROJECT(ahti)


#############
# Add main source file 
#############

SET(MAIN_SRC_FILE "main.cu")


#-------------------------------------------------------------------------------
# Find alpaka.
#-------------------------------------------------------------------------------

SET(ALPAKA_ROOT "${CMAKE_CURRENT_LIST_DIR}/../utils/alpaka" CACHE STRING "The location of the alpaka library")
LIST(APPEND CMAKE_MODULE_PATH "${ALPAKA_ROOT}")
FIND_PACKAGE("alpaka" REQUIRED)
if(ALPAKA_FOUND)
message("-- alapaka detected")
endif(ALPAKA_FOUND)


###############
# Find Graybar
###############
SET(GRAYBAT_ROOT " ${CMAKE_CURRENT_LIST_DIR}/../utils/graybat/utils/cmake/modules/" CACHE STRING "The location of the graybat library")
LIST(APPEND CMAKE_PREFIX_PATH "${GRAYBAT_ROOT}")
SET(graybat_DIR "${CMAKE_CURRENT_LIST_DIR}/../utils/graybat")
FIND_PACKAGE("graybat" REQUIRED)
if(graybat_FOUND)
	message("-- Graybat detected")
endif(graybat_FOUND)

#############
# Include directory
#############
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR}/../include/*)



#############
# Add executable
#############

ALPAKA_ADD_EXECUTABLE(ahti ${MAIN_SRC_FILE})
