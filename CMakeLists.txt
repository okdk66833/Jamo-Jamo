cmake_minimum_required(VERSION 3.10)
project(JamoJamo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{BOOST_ROOT})
    set(BOOST_INCLUDE_DIR "$ENV{BOOST_ROOT}/include")
else()
    find_path(BOOST_INCLUDE_DIR boost/nowide/convert.hpp)
endif()

add_library(jamojamo STATIC jamojamo.cpp include/jamojamo.h)
target_include_directories(jamojamo PUBLIC include)
target_include_directories(jamojamo PRIVATE ${BOOST_INCLUDE_DIR})

add_executable(JamoJamoExample examples/main.cpp)
target_link_libraries(JamoJamoExample PRIVATE jamojamo)
