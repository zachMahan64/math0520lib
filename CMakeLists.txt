cmake_minimum_required(VERSION 3.20)

project(Demo)
set(EXECUTABLE demo)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC src/main.cpp)

set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -Wextra -Wpedantic -g" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG" CACHE STRING "" FORCE)

add_executable(${EXECUTABLE} ${SRC})
target_include_directories(${EXECUTABLE} PRIVATE src)

add_subdirectory(math0520lib)
target_link_libraries(demo PRIVATE math0520lib)
