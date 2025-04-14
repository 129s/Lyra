cmake_minimum_required(VERSION 3.10.0)

project(Lyra VERSION 0.1.0 LANGUAGES C CXX)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(${CMAKE_SOURCE_DIR}/include)

aux_source_directory(src SOURCES)
add_executable(${PROJECT_NAME} 
    example/test.cpp
    ${SOURCES}
)

target_link_libraries(Lyra PRIVATE winmm)

