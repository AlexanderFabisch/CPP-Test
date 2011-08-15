cmake_minimum_required(VERSION 2.8)
project(CPPTest)
find_package(Qt4 REQUIRED)
include_directories(
  "."
  ${QT_LIB_DIR}
)

set(QT_USE_QTMAIN TRUE)
include(${QT_USE_FILE})

add_definitions(
  -Wall
  -ggdb
  ${QT_DEFINITIONS}
)

qt4_wrap_cpp(MOC_OUTPUT_UNIT
  Test/QtTestRunner.h
)
add_library(unit
  ${MOC_OUTPUT_UNIT}
  Test/Observable.cpp
  Test/TextTestRunner.cpp
  Test/QtTestRunner.cpp
  Test/TestResult.cpp
  Test/TestSuite.cpp
)

add_executable(CPPTest test.cpp)
target_link_libraries(CPPTest unit ${QT_LIBRARIES})
