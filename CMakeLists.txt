# CMakeList.txt: Lyra 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lyra")

# 将源代码添加到此项目的可执行文件。
add_executable (Lyra "Lyra.cpp" "Lyra.h" "include/vst2.x/aeffect.h" "include/vst2.x/aeffectx.h" "include/vst2.x/aeffeditor.cpp" "include/vst2.x/aeffeditor.h" "include/vst2.x/audioeffect.cpp" "include/vst2.x/audioeffectx.cpp" "include/vst2.x/audioeffectx.h" "include/vst2.x/vstevent.h" "include/vst2.x/vstkey.h" "include/vst2.x/vstmidi.h" "include/vst2.x/vstparameter.h" "include/vst2.x/vstpin.h" "include/vst2.x/vstspeaker.h" "include/vst2.x/vsttime.h" "include/vst2.x/vsttypes.h" "include/vst2.x/vstversion.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lyra PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
