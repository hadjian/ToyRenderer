# CMakeLists.txt for the Src subdirectory.

# Make available the Qt libraries and macros.
find_package(Qt5Widgets REQUIRED)

add_library(toyrenderengine SHARED 
             toyrenderengine.cpp
             toygeometry.cpp 
             toyrenderhelper.cpp
             ${CMAKE_SOURCE_DIR}/Include/toygeometry.h 
             ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h
             ${CMAKE_SOURCE_DIR}/Include/toyrenderhelper.h)
target_link_libraries(toyrenderengine ${QT_LIBRARIES})
qt5_use_modules(toyrenderengine Core)
