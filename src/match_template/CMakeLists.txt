cmake_minimum_required(VERSION 3.0.0)
project(match_template LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED HINTS ${CMAKE_SOURCE_DIR}/thirdparty/OpenCV/install/lib/cmake/opencv4)

if(OpenCV_FOUND)
    message(STATUS "opencv found!! -${OpenCV_DIR}")
endif()

# add_executable(match_template template.cpp)
# add_executable(match_template find_items.cpp)
# add_executable(match_template digit_gen.cpp)
add_executable(match_template digit_rec.cpp)

target_include_directories(match_template PUBLIC
    ${OpenCV_INCLUDE_DIRS}
    )
target_link_libraries(match_template ${OpenCV_LIBS})

