cmake_minimum_required(VERSION 3.20)

project(math0520lib)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(math0520lib SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vec_operations.cpp
)

target_include_directories(math0520lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)
