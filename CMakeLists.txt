# CMakeList.txt: plik projektu CMake najwyższego poziomu, wykonaj konfigurację globalną
# i uwzględnij podprojekty w tym miejscu.
#
cmake_minimum_required (VERSION 3.8)

# Włącz przeładowywanie kodu XAML na gorąco dla kompilatorów MSVC, jeśli jest to obsługiwane.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Snake3D")

include_directories(  "external/glad/include" )
include_directories(  "external/glm/include" )
#include_directories(  "external/GLFW/include" )
include_directories(  "external/assimp/include" )
include_directories(  "external/KHR/include" )
include_directories(  "external/freetype/freetype/include" )
include_directories(  "external/irrKlang/include" )

# Uwzględnij podprojekty.
add_subdirectory("external/freetype/freetype")
add_subdirectory("external/assimp")
add_subdirectory ("Snake3D")
