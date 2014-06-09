# CMakeLists.txt for the Src subdirectory.

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt5 modules and OpenGL explicitly.
find_package(OpenGL     REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core    REQUIRED)
find_package(Qt5OpenGL  REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_library(GLEW_LIBRARY GLEW)

# The following will also set the compiler definitions.
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(toyrendererexample_FORMS mainwindow.ui)
QT5_WRAP_UI(toyrendererexample_FORMS_HEADERS ${toyrendererexample_FORMS})

add_executable(toyrendererexample
                 main.cpp
                 toyglwidget.cpp
                 toymainwindow.cpp
                 ${toyrendererexample_FORMS_HEADERS}
                 ${CMAKE_SOURCE_DIR}/Include/toygeometry.h
                 ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(toyrendererexample toyrenderengine ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
qt5_use_modules(toyrendererexample OpenGL Core Gui Widgets)
