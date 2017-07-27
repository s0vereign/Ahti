############
# Use CMake 3.3.0
############

CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

############
# Add subdirectories
############

#ADD_SUBDIRECTORY(./utils)
add_subdirectory("./utils/googletest")
ADD_SUBDIRECTORY(./src)
