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

# Chesser
project("Chesser")
add_subdirectory("Nibble")

file(GLOB_RECURSE chesser_srcs "src/*.cpp")
file(GLOB_RECURSE chesser_hdrs "src/*.h")

include_directories("src/")
include_directories("Nibble/src/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D static_link")

add_executable(
    "Chesser"

    ${chesser_srcs}
    ${chesser_hdrs}
    )

target_link_libraries("Chesser" "Nibble") 
cotire("Chesser")
