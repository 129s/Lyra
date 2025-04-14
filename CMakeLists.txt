cmake_minimum_required(VERSION 3.10.0)
project(Lyra VERSION 0.1.0 LANGUAGES C CXX)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(Lyra src/main.cpp)
