cmake_minimum_required(VERSION 3.10)

PROJECT(extMariaDB)

# verbose makefiles
#SET(CMAKE_VERBOSE_MAKEFILE ON)

INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

# this helps debugging dependencies - a lot :)
#SET_PROPERTY(GLOBAL PROPERTY GLOBAL_DEPENDS_DEBUG_MODE 1)

ADD_SUBDIRECTORY(MariaDB)
