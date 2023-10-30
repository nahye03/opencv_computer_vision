cmake_minimum_required(VERSION 3.0.0)
project(extract_feature LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if(OpenCV_FOUND)
    message(STATUS "opencv found!! -${OpenCV_DIR}")
endif()


# add_executable(detect_edge sobel.cpp)
# add_executable(detect_edge houghlines.cpp)
# add_executable(detect_edge houghcircle.cpp)
add_executable(detect_edge corners.cpp)

# add_library(detect_edge mycanny.cpp)
target_include_directories(detect_edge PUBLIC
    include
    ${OpenCV_INCLUDE_DIRS}
    )
target_link_libraries(detect_edge ${OpenCV_LIBS})

# add_executable(canny canny.cpp)
# target_link_libraries(canny
#     detect_edge
#     )


