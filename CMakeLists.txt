cmake_minimum_required(VERSION 3.10)

# 全局设置
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 编译器优化
if (MSVC)
    add_compile_options(
        /O2     # 最大优化
        /GL     # 全程序优化
        /arch:SSE2
        /GR-    # 禁用 RTTI
        /EHa-   # 禁用异常
        /fp:fast
    )
    add_link_options(/LTCG)
else()
    add_compile_options(
        -Os
        -ffunction-sections
        -fdata-sections
        -fno-rtti
        -fno-exceptions
        -ffast-math
    )
    add_link_options(-Wl,--gc-sections)
endif()

project(Lyra VERSION 0.1.0 LANGUAGES C CXX)

# 目标配置
add_executable(${PROJECT_NAME} 
    # WIN32 # 禁用控制台窗口
    example/test.cpp
    src/audio.cpp
    src/host.cpp
    src/midi.cpp
    src/sine_wave.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE winmm)