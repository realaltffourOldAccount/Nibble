cmake_minimum_required(VERSION 3.5)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SKIP_INSTALL_RULES ON)

message("${CMAKE_CXX_COMPILER_ID}")

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Compiler Specific Commands, Cross-Platform
if(MSVC)
    # Microsoft visual studio
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /SUBSYSTEM:WINDOWS /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # GNU compilers
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wno-long-long")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows -Wno-long-long")
endif()

# Set Definetions
if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
    add_definitions(-D__DEBUG__)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Release") 
    add_definitions(-D__RELEASE__)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

if (WEB)
    add_definitions(-D__CHEERP__)
    add_definitions(-D__WEB__)
endif()

# Libraries

# Desktop Only Libraries
if (NOT WEB)
    # GLFW
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory("deps/GLFW/")

    # GLAD
    add_subdirectory("deps/GLAD/")

    # End of Desktop Only Libraries
endif()

# Cross-Platform Libraries
# GLM
set(GLM_QUIET OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory("deps/GLM/")

# Freetype
add_subdirectory("deps/freetype/")
include_directories("deps/freetype/include/freetype/")

# Options of google's libraries
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

set(BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# GLOG
add_subdirectory("deps/glog")

# GFLAGS
add_subdirectory("deps/gflags")

project("Nibble")

file(GLOB_RECURSE Nibble_srcs "src/*.cpp")
file(GLOB_RECURSE Nibble_hdrs "src/*.h")

include_directories("src/")
include_directories("deps/GLFW/include")
include_directories("deps/GLAD/include")
include_directories("deps/GLM/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D static_link")

add_library(
    "Nibble"

    ${Nibble_srcs}
    ${Nibble_hdrs}
    )
if (NOT WEB)
    target_link_libraries("Nibble" glfw ${GLFW_LIBRARIES} glad glm glog::glog gflags::gflags freetype) 
endif()
if (WEB)
    target_link_libraries("Nibble" glm glog::glog gflags::gflags freetype) 
endif()
cotire("Nibble")
