cmake_minimum_required(VERSION 2.8)
project(ToyMatrix_UnitTests)

option(ArithmeticExceptions "Check Include/arithmeticex.h for a list of exceptions. 
                             Turn on to help you hunt bugs (but run less efficiently)." OFF)

if (ArithmeticExceptions)
  add_definitions( -DARITHMETIC_EXCEPTIONS )
endif(ArithmeticExceptions)

# Make available the Qt libraries and macros.
find_package(Qt4 REQUIRED QtCore)

# The following will also set the compiler definitions.
include(${QT_USE_FILE})

# Create our unit tests.
add_executable(testtoyrenderengine testtoyrenderengine.cpp ${CMAKE_SOURCE_DIR}/Include/toygeometry.h ${CMAKE_SOURCE_DIR}/Include/toyrenderengine.h)
target_link_libraries(testtoyrenderengine ${GTEST_MAIN_LIBRARIES} toyrenderengine)
set_target_properties(testtoyrenderengine PROPERTIES
                       COMPILE_FLAGS ${GTEST_CXX_FLAGS})

add_executable(testtoyrenderhelper testtoyrenderhelper.cpp ${CMAKE_SOURCE_DIR}/Include/toyrenderhelper.h)
target_link_libraries(testtoyrenderhelper ${GTEST_MAIN_LIBRARIES} toyrenderengine)
set_target_properties(testtoyrenderhelper PROPERTIES
                       COMPILE_FLAGS ${GTEST_CXX_FLAGS})
