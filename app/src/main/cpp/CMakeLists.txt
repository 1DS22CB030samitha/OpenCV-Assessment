cmake_minimum_required(VERSION 3.22.1)
project("edge-detection")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenCV
set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../../../opencv/sdk/native/jni")
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
add_library(edge-detection SHARED
    native-lib.cpp
    edge_processor.cpp
    opengl_renderer.cpp
)

# Link libraries
target_link_libraries(edge-detection
    ${OpenCV_LIBS}
    android
    log
    GLESv2
    EGL
)

# For OpenCV static linking (if needed)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

