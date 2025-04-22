cmake_minimum_required(VERSION 3.15)
project(Lyra C)

# 优化编译体积
set(CMAKE_C_STANDARD 11)

# 目标配置
aux_source_directory(src SOURCES)
add_executable(${PROJECT_NAME} WIN32
    example/test.c
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Windows特定API链接
if(WIN32)
    target_link_libraries(${PROJECT_NAME}  winmm)
endif()

