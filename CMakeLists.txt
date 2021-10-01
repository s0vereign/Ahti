############
# Use CMake 3.3.0
############

CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

############
# Define project
############

PROJECT(ahti)
include(FetchContent)

############
# Add subdirectories
############

#ADD_SUBDIRECTORY("./utils/googletest/googletest")
ADD_SUBDIRECTORY(./src)
