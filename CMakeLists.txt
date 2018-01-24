cmake_minimum_required (VERSION 2.6)
project (cscshell C CXX)

# location of header files
include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB SOURCES src/*.c)
list(REMOVE_ITEM SOURCES ${PROJECT_SOURCE_DIR}/src/cscshell.c)
file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/spec/*.cpp)

add_executable(cscshell ${PROJECT_SOURCE_DIR}/src/cscshell.c)
target_link_libraries(cscshell ${SOURCES})

enable_testing()

find_package(GTest REQUIRED)

add_executable(runUnitTests ${TEST_SOURCES})
target_link_libraries(runUnitTests GTest::GTest GTest::Main)

add_test(UnitTests runUnitTests)
