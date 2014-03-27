# CMakeLists.txt for the Src subdirectory.

# Make available the Qt libraries and macros.
find_package(Qt4 REQUIRED QtCore)

# The following will also set the compiler definitions.
include(${QT_USE_FILE})

add_library(toyrenderengine SHARED toyrenderengine.cpp toygeometry.cpp ${CMAKE_SOURCE_DIR}/Include/toygeometry.h ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(toyrenderengine ${QT_LIBRARIES})
