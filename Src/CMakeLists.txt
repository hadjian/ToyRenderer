# CMakeLists.txt for the Src subdirectory.

find_package(Qt5Core)
include_directories(${Qt5Core_INCLUDE_DIRS})
add_definitions(${Qt5Core_DEFINITIONS})

add_library(toyrenderengine SHARED 
             toyrenderengine.cpp
             toygeometry.cpp 
             toyrenderhelper.cpp
             ${CMAKE_SOURCE_DIR}/Include/toygeometry.h 
             ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h
             ${CMAKE_SOURCE_DIR}/Include/toyrenderhelper.h)
target_link_libraries(toyrenderengine Qt5::Core)
