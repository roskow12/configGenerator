cmake_minimum_required(VERSION 3.9)
project(configAndRules)

set(CMAKE_CXX_STANDARD 14)

include (ExternalProject)

ExternalProject_Add( boost
    PREFIX boost
    URL https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2
    URL_HASH SHA256=5721818253e6a0989583192f96782c4a98eb6204965316df9f5ad75819225ca9
    CONFIGURE_COMMAND ./bootstrap.sh --with-libraries=system
    BUILD_COMMAND ./b2 link=static threading=multi
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ""
)

set(Boost_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/boost/src/boost)
set(Boost_Libraries ${CMAKE_CURRENT_BINARY_DIR}/boost/src/boost/stage/lib)
# set(Boost_USE_STATIC_LIBS ON) # only find static libs
# set(Boost_USE_MULTITHREADED ON)
# set(Boost_NO_SYSTEM_PATHS ON)
# set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/ep_boost")

# find_package(Boost 1.66 COMPONENTS system REQUIRED)

add_library(json STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/json/json.hpp")
set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(json PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/json")

add_library(configGenerator INTERFACE)
target_include_directories(configGenerator INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src/config_generator")

add_library(http STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/http/http_worker.hpp")
set_target_properties(http PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(http PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/http" ${Boost_INCLUDE_DIRS})
add_dependencies(http boost)
target_link_libraries(http pthread configGenerator json ${Boost_Libraries})

add_executable(configAndRules src/main.cpp)
target_compile_options(configAndRules PUBLIC -g -Wall -pedantic -Wextra -O3)
target_link_libraries(configAndRules http)