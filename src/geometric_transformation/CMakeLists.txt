cmake_minimum_required(VERSION 3.0.0)
project(geometric_tranformation LANGUAGES CXX)
message(STATUS "Project name - ${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if(OpenCV_FOUND)
    message(STATUS "OpenCV found - ${OpenCV_DIR}")
endif()

# add_executable(transformation translation.cpp)
# add_executable(transformation shear.cpp)
# add_executable(transformation resize.cpp)
# add_executable(transformation rotate.cpp)
add_executable(transformation birdeye.cpp)
# add_executable(transformation remap.cpp)

target_include_directories(transformation PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    )
target_link_libraries(transformation ${OpenCV_LIBS})
