cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(cotire)

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
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wno-long-long")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -mwindows -Wall -Wno-long-long")
endif()

# Set Definetions
if (CMAKE_BUILD_TYPE STREQUAL "Debug") 
  add_definitions(-D__DEBUG__)
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Release") 
  add_definitions(-D__RELEASE__)
endif (CMAKE_BUILD_TYPE STREQUAL "Release")

if (EMSCRIPTEN)
  add_definitions(-D__EMSCRIPTEN__)
endif()

# Libraries

# Desktop Only Libraries
if (NOT EMSCRIPTEN)
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("deps/GLFW/")

# GLAD
add_subdirectory("deps/GLAD/")

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

# End of Desktop Only Libraries
endif()

# Emscripten Only Libraries
if (EMSCRIPTEN)

# Freetype-Emscripten
add_subdirectory("deps/freetype-em/")
include_directories("deps/freetype-em/include")

# End of Emscripten Only Libraries
endif()

# Cross-Platform Libraries
# GLM
set(GLM_QUIET OFF CACHE BOOL "" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
add_subdirectory("deps/GLM/")
# End of Cross-Platform Libraries

# End of Libraries

# Chesser
if (NOT EMSCRIPTEN)
project("Chesser")

file(GLOB_RECURSE chesser_srcs "Chesser/*.cpp")
file(GLOB_RECURSE chesser_hdrs "Chesser/*.h")

include_directories("Chesser/")
include_directories("deps/GLFW/include")
include_directories("deps/GLAD/include")
include_directories("deps/GLM/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D static_link")

add_executable(
    "Chesser"

    ${chesser_srcs}
    ${chesser_hdrs}
)

target_link_libraries("Chesser" glfw ${GLFW_LIBRARIES} glad glm glog::glog gflags::gflags freetype) 
cotire("Chesser")
endif()

# Chesser Emscripten
if (EMSCRIPTEN)

project ("Chesser_EMCC")

add_definitions(-D__EMSCRIPTEN__)

include_directories("Chesser/")
include_directories("deps/GLFW/include")
include_directories("deps/GLAD/include")
include_directories("deps/GLM/")
include_directories("deps/spdlog/include/")

include_directories("Chesser/vendor/imgui/")

file(GLOB_RECURSE chesser_srcs "Chesser/*.cpp")
file(GLOB_RECURSE chesser_hdrs "Chesser/*.h")

add_executable(
    "Chesser_EMCC"

    ${chesser_srcs}
    ${chesser_hdrs}
)
# Link 3rd-party deps
target_link_libraries("Chesser_EMCC" glm freetype)

# Use WebGL3 And GLFW3 and stb_image
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FULL_ES3=3 -s USE_GLFW=3 -s STB_IMAGE=1")

# Set debug only options
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O1 -g -s ASSERTIONS=2")

# Set release only options
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 ")

# Set Secondary Options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 --emrun --preload-file ${CMAKE_SOURCE_DIR}/assets@/assets --preload-file ${CMAKE_SOURCE_DIR}/Chesser/engine/glsl@/glsl")

# Generate HTML
set(CMAKE_EXECUTABLE_SUFFIX ".html")

endif()

# Copy files
file(COPY assets DESTINATION bin)
file(COPY Chesser/engine/glsl DESTINATION bin)