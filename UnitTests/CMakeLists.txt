cmake_minimum_required(VERSION 2.8)
project(ToyMatrix_UnitTests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find Qt5 modules and OpenGL explicitly.
find_package(OpenGL     REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core    REQUIRED)
find_package(Qt5OpenGL  REQUIRED)
find_package(Qt5Gui     REQUIRED)
find_library(GLEW_LIBRARY GLEW)

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

option(ArithmeticExceptions "Check Include/arithmeticex.h for a list of exceptions. 
                             Turn on to help you hunt bugs (but run less efficiently)." OFF)

add_definitions( -DGTEST_USE_OWN_TR1_TUPLE=1 )

if (ArithmeticExceptions)
  add_definitions( -DARITHMETIC_EXCEPTIONS )
endif(ArithmeticExceptions)

# Create our unit tests.
add_executable(testtoyrenderengine testtoyrenderengine.cpp ${CMAKE_SOURCE_DIR}/Include/toygeometry.h ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(testtoyrenderengine ${GTEST_MAIN_LIBRARIES} toyrenderengine Qt5::Widgets Qt5::Core Qt5::OpenGL Qt5::Gui)
if (NOT "${GTEST_CXX_FLAGS}" STREQUAL "")
  set_target_properties(testtoyrenderengine PROPERTIES
                         COMPILE_FLAGS ${GTEST_CXX_FLAGS})
endif()

add_executable(testtoyrenderhelper testtoyrenderhelper.cpp ${CMAKE_SOURCE_DIR}/Include/toyrenderhelper.h)
target_link_libraries(testtoyrenderhelper ${GTEST_MAIN_LIBRARIES} toyrenderengine Qt5::Widgets Qt5::Core Qt5::OpenGL Qt5::Gui)
if (NOT "${GTEST_CXX_FLAGS}" STREQUAL "")
  set_target_properties(testtoyrenderhelper PROPERTIES
                         COMPILE_FLAGS ${GTEST_CXX_FLAGS})
endif()
