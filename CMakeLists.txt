cmake_minimum_required(VERSION 3.10)
project(JamoJamo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
set(BOOST_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")

add_library(jamojamo STATIC jamojamo.cpp jamojamo.hpp)
target_include_directories(jamojamo PUBLIC .)
target_include_directories(jamojamo PRIVATE ${BOOST_INCLUDE_DIR})

add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE jamojamo)
target_include_directories(demo PRIVATE ${BOOST_INCLUDE_DIR})
