cmake_minimum_required(VERSION 3.0.0)
project(process_binary LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if(OpenCV_FOUND)
    message(STATUS "opencv found!! -${OpenCV_DIR}")
endif()

add_executable(process_binary threshold.cpp)
# add_executable(process_binary otsu.cpp)
# add_executable(process_binary local_th.cpp)
# add_executable(process_binary adapt_th.cpp)
# add_executable(process_binary rice_count.cpp)
# add_executable(process_binary labeling.cpp)
# add_executable(process_binary keyseg.cpp)
# add_executable(process_binary contours1.cpp)
# add_executable(process_binary contours2.cpp)
# add_executable(process_binary polygon.cpp)

target_include_directories(process_binary PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    )
target_link_libraries(process_binary ${OpenCV_LIBS})

