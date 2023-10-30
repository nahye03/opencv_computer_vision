cmake_minimum_required(VERSION 3.0.0)
project(feature_point LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if (OpenCV_FOUND)
	message(STATUS "opencv found!! - ${OpenCV_DIR}")
endif()

# add_executable(feature_point keypoint.cpp)
# add_executable(feature_point matching_keypoints.cpp)
add_executable(feature_point matching.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(feature_point ${OpenCV_LIBS})
