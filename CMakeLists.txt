cmake_minimum_required (VERSION 2.8)
project (ToyRenderer)

# The version number.
set (ToyRenderer_VERSION_MAJOR 0)
set (ToyRenderer_VERSION_MINOR 1)

find_package(ToyMatrix 0.1.0 EXACT REQUIRED)

include_directories(${PROJECT_SOURCE_DIR} ${TOYMATRIX_INCLUDE_DIRS})

add_subdirectory(Src)
