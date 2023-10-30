cmake_minimum_required(VERSION 3.0.0)
project(color_img_op LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if (OpenCV_FOUND)
	message(STATUS "opencv found!! - ${OpenCV_DIR}")
endif()

# add_executable(color_img_op color.cpp)
# add_executable(color_img_op split.cpp)
# add_executable(color_img_op color_eq.cpp)
# add_executable(color_img_op color_tone.cpp)
# add_executable(color_img_op inrange.cpp)
# add_executable(color_img_op backproj1.cpp)
add_executable(color_img_op backproj2.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(color_img_op ${OpenCV_LIBS})
