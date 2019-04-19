cmake_minimum_required(VERSION 3.1)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Compiler Specific Commands, Cross-platform
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wno-long-long")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows -Wall -Wno-long-long")
endif()

# Set Defines
if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
  add_definitions(-D__DEBUG__)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Release") 
  add_definitions(-D__RELEASE__)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("deps/GLFW/")

# GLAD
add_subdirectory("deps/GLAD/")

# vmmlib
include_directories("deps/vmmlib/")

# spdlog
add_subdirectory("deps/spdlog/")

# Chesser
project("Chesser")

file(GLOB_RECURSE chesser_srcs "Chesser/*.cpp")
file(GLOB_RECURSE chesser_hdrs "Chesser/*.h")

include_directories("Chesser/")
include_directories("deps/GLFW/include")
include_directories("deps/GLAD/include")
include_directories("deps/GLM/")
include_directories("deps/spdlog/include/")

add_executable(
    "Chesser"

    ${chesser_srcs}
    ${chesser_hdrs}
)
target_link_libraries("Chesser" glfw ${GLFW_LIBRARIES} glad)
