cmake_minimum_required(VERSION 3.5)
#set(CMAKE_SKIP_INSTALL_RULES ON)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GLFM
add_subdirectory("deps/GLFM/")

# GLM
set(GLM_QUIET OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory("deps/GLM/")

# Options of google's libraries
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# gflags
add_subdirectory("deps/gflags/")

# miniglog
# add_subdirectory("deps/miniglog/")
add_library(miniglog "deps/miniglog/glog/logging.h" "deps/miniglog/glog/logging.cc")

# Freetype
set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE CACHE BOOL "" FORCE)
set(FT_WITH_ZLIB FALSE CACHE BOOL "" FORCE)
add_subdirectory("deps/freetype/")

# Chesser
file(GLOB_RECURSE chesser_srcs "Chesser/*.cpp")
file(GLOB_RECURSE chesser_hdrs "Chesser/*.h")

include_directories("deps/GLFM/include/")
include_directories("deps/miniglog/")
include_directories("Chesser/")
add_definitions(-D__ANDROID__)
add_library(Chesser_lib SHARED ${chesser_hdrs} ${chesser_srcs} )
#add_library(Chesser_lib SHARED native-lib.cpp)

target_link_libraries(Chesser_lib glfm glm miniglog gflags::gflags freetype)