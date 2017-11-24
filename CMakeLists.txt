############
# Use CMake 3.3.0
############

CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

############
# Add subdirectories
############

ADD_SUBDIRECTORY("./utils/googletest/googletest")
ADD_SUBDIRECTORY(./src)
