cmake_minimum_required(VERSION 2.8)
project(ToyMatrix_UnitTests)

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

option(ArithmeticExceptions "Check Include/arithmeticex.h for a list of exceptions. 
                             Turn on to help you hunt bugs (but run less efficiently)." OFF)

add_definitions( -DGTEST_USE_OWN_TR1_TUPLE=1 )

if (ArithmeticExceptions)
  add_definitions( -DARITHMETIC_EXCEPTIONS )
endif(ArithmeticExceptions)

# Create our unit tests.
add_executable(testtoyrenderengine testtoyrenderengine.cpp ${CMAKE_SOURCE_DIR}/Include/toygeometry.h ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(testtoyrenderengine ${GTEST_MAIN_LIBRARIES} ${OPENGL_LIBRARIES} toyrenderengine)
if (NOT "${GTEST_CXX_FLAGS}" STREQUAL "")
  set_target_properties(testtoyrenderengine PROPERTIES
                         COMPILE_FLAGS ${GTEST_CXX_FLAGS})
endif()
qt5_use_modules(testtoyrenderengine OpenGL Core Gui Widgets)

add_executable(testtoyrenderhelper testtoyrenderhelper.cpp ${CMAKE_SOURCE_DIR}/Include/toyrenderhelper.h)
target_link_libraries(testtoyrenderhelper ${GTEST_MAIN_LIBRARIES} ${OPENGL_LIBRARIES} toyrenderengine)
if (NOT "${GTEST_CXX_FLAGS}" STREQUAL "")
  set_target_properties(testtoyrenderhelper PROPERTIES
                         COMPILE_FLAGS ${GTEST_CXX_FLAGS})
endif()
qt5_use_modules(testtoyrenderhelper OpenGL Core Gui Widgets)
