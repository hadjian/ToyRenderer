# CMakeLists.txt for the Src subdirectory.

find_package(Qt4 REQUIRED QtCore QtGui QtOpenGL)
find_library(GLEW_LIBRARY GLEW)

set(toyrenderer_SOURCES main.cpp toyglwidget.cpp toymainwindow.cpp toyrenderengine.cpp)  
# toyrenderer_HEADERS is currently empty. Leaving here for reference.
set(toyrenderer_HEADERS )
set(toyrenderer_FORMS mainwindow.ui)
 
QT4_WRAP_UI(toyrenderer_FORMS_HEADERS ${toyrenderer_FORMS})
QT4_WRAP_CPP(toyrenderer_HEADERS_MOC ${toyrenderer_HEADERS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(toyrenderer ${toyrenderer_SOURCES} ${toyrenderer_HEADERS_MOC} ${toyrenderer_FORMS_HEADERS})
target_link_libraries(toyrenderer ${QT_LIBRARIES} ${GLEW_LIBRARY})
