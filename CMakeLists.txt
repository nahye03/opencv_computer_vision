cmake_minimum_required(VERSION 3.0.0)
project(computer_vision LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(src/feature_point)
# add_subdirectory(src/color_img_op)
# add_subdirectory(src/extract_feature)
# add_subdirectory(src/process_binary)
# add_subdirectory(src/match_template)
add_subdirectory(src/geometric_transformation)
