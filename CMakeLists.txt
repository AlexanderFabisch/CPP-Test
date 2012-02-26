project(CPPTest)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4)

set(INCLUDE_DIRS ".")
set(COMPILE_DEFS "-Wall -ggdb")

if(QT_FOUND)
  message(STATUS "Found Qt")
  set(QT_USE_QTMAIN TRUE)
  include(${QT_USE_FILE})
  set(INCLUDE_DIRS "${INCLUDE_DIRS} ${QT_LIB_DIR}")
  set(COMPILE_DEFS "${COMPILE_DEFS} ${QT_DEFINITIONS} -DCPPTEST_USE_QT")
endif()

include_directories(${INCLUDE_DIRS})
add_definitions(${COMPILE_DEFS})

if(QT_FOUND)
  qt4_wrap_cpp(MOC_OUTPUT_UNIT Test/QtTestRunner.h)
  add_library(unit
      Test/Observable.cpp
      Test/TestResult.cpp
      Test/TestSuite.cpp
      Test/TextTestRunner.cpp
      Test/QtTestRunner.cpp
      ${MOC_OUTPUT_UNIT})
  target_link_libraries(unit ${QT_LIBRARIES})
else()
  add_library(unit
      Test/Observable.cpp
      Test/TestResult.cpp
      Test/TestSuite.cpp
      Test/TextTestRunner.cpp)
endif()

add_executable(CPPTest test.cpp)
target_link_libraries(CPPTest unit)