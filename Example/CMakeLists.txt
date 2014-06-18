# CMakeLists.txt for the Src subdirectory.

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt5 modules and OpenGL explicitly.
find_package(OpenGL     REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core    REQUIRED)
find_package(Qt5OpenGL  REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_library(GLEW_LIBRARY GLEW)
find_path(GLEW_INCLUDE  GL/glew.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5OpenGL_DEFINITIONS})
add_definitions(${Qt5Gui_DEFINITIONS})

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${GLEW_INCLUDE})

QT5_WRAP_UI(toyrendererexample_FORMS_HEADERS mainwindow.ui) 

add_executable(toyrendererexample
                 main.cpp
                 toyglwidget.cpp
                 toymainwindow.cpp
                 ${toyrendererexample_FORMS_HEADERS}
                 ${CMAKE_SOURCE_DIR}/Include/toygeometry.h
                 ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(toyrendererexample toyrenderengine ${GLEW_LIBRARY} Qt5::Widgets Qt5::Core Qt5::OpenGL Qt5::Gui)
