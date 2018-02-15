cmake_minimum_required(VERSION 3.9)
project(configAndRules)

set(CMAKE_CXX_STANDARD 14)

message("includir: ${Boost_INCLUDE_DIR}")

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)

find_package(Boost 1.66 COMPONENTS system REQUIRED)

add_library(json STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/json/json.hpp")
set_target_properties(json PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(json PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/json")


add_library(configGenerator INTERFACE)
target_include_directories(configGenerator INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src/config_generator")

add_library(http STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/http/http_worker.hpp")
set_target_properties(http PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(http PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/http")
target_link_libraries(http ${Boost_SYSTEM_LIBRARY} pthread configGenerator json)

add_executable(configAndRules src/main.cpp)
target_compile_options(configAndRules PUBLIC -g -Wall -pedantic -Wextra -O3)
target_link_libraries(configAndRules http)