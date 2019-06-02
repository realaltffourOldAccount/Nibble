set(GLM_VERSION "0.9.9")
set(GLM_INCLUDE_DIRS "/home/akham/Desktop/Chesser/Chesser_android/app/src/main/cpp/deps/GLM")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
