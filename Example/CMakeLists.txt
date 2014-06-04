# CMakeLists.txt for the Src subdirectory.

# Make available the Qt libraries and macros.
find_package(Qt4 REQUIRED QtCore QtGui QtOpenGL)
find_library(GLEW_LIBRARY GLEW)

# The following will also set the compiler definitions.
include(${QT_USE_FILE})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(toyrendererexample_FORMS mainwindow.ui)
QT4_WRAP_UI(toyrendererexample_FORMS_HEADERS ${toyrendererexample_FORMS})

add_executable(toyrendererexample
                 main.cpp
                 toyglwidget.cpp
                 toymainwindow.cpp
                 ${toyrendererexample_FORMS_HEADERS}
                 ${CMAKE_SOURCE_DIR}/Include/toygeometry.h
                 ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(toyrendererexample toyrenderengine ${QT_LIBRARIES} ${GLEW_LIBRARY})
