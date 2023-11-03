cmake_minimum_required(VERSION 3.10)
project(machine_and_deep VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if(OpenCV_FOUND)
    message(STATUS "opencv found - ${OpenCV_DIR}")
endif()

# add_executable(${PROJECT_NAME} facedetect.cpp)
add_executable(${PROJECT_NAME} svmplane.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
