cmake_minimum_required(VERSION 3.28)
project(Arc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Arc src/main.cpp)
