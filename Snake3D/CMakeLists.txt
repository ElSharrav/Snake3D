# CMakeList.txt: projekt CMake dla elementu SnakeCmake, dołącz źródło i zdefiniuj
# tutaj logikę specyficzną dla projektu.
#

set( STB_SOURCE_FILES
	source/stb_image/stb_imageImp.cpp
)

set( GLFW_SOURCE_FILES
	source/glfw/Glfw.cpp
)

set( GLAD_SOURCE_FILES
	source/glad/Glad.cpp
)

set( ENGINE_SOURCE_FILES
	source/engine/camera/camera.cpp source/engine/colors/Color.cpp source/engine/cubemap/Cubemap.cpp  source/engine/files/File.cpp source/engine/files/InitializationFile.cpp source/engine/fonts/Fonts.cpp source/engine/framebuffer/Framebuffer.cpp source/engine/lightning/light.cpp source/engine/lightning/material.cpp
	source/engine/models/mesh.cpp source/engine/models/model.cpp source/engine/particles/ParticlesGenerator.cpp source/engine/primitives/cube.cpp source/engine/primitives/line.cpp source/engine/primitives/NDCquad.cpp source/engine/primitives/Point3d.cpp source/engine/primitives/triangle.cpp source/engine/primitives/Vec2.cpp source/engine/Random/Random.cpp
	 source/engine/resources/ResourceLoader.cpp source/engine/resources/ResourceManager.cpp source/engine/resources/Sounds.cpp source/engine/shaders/shader.cpp source/engine/shaders/shaderProgram.cpp source/engine/string/StringOperations.cpp source/engine/texture/texture.cpp source/engine/engine.cpp
)

set( SNAKE_IMPLEMENTATION
	source/snakeImplementation/Options/MenuOption.cpp source/snakeImplementation/Options/OptionsScreen.cpp source/snakeImplementation/board.cpp source/snakeImplementation/Game.cpp source/snakeImplementation/GameManager.cpp source/snakeImplementation/GameMenu.cpp source/snakeImplementation/HighScores.cpp source/snakeImplementation/HighScoreScreen.cpp
	 source/snakeImplementation/MapEditor.cpp source/snakeImplementation/MapNames.cpp source/snakeImplementation/OptionsScreenImpl.cpp source/snakeImplementation/SelectLevelScreen.cpp source/snakeImplementation/SelectLevelScreen.cpp source/snakeImplementation/Snake.cpp source/snakeImplementation/snakeHead.cpp source/snakeImplementation/SnakeTail.cpp
)

# GLFW

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3
)

FetchContent_MakeAvailable(glfw)

#glad

add_library(glad STATIC ../external/glad/src/glad.c)
target_include_directories(glad PUBLIC ../external/glad/include)

#irrklang

set(IRRKLANG_DIR ${CMAKE_SOURCE_DIR}/external/irrKlang)

if (WIN32)
    set(IRRKLANG_LIB ${IRRKLANG_DIR}/lib/irrKlang.lib)
elseif (UNIX)
    set(IRRKLANG_LIB ${IRRKLANG_DIR}/lib/libIrrKlang.so)
endif()

# Dodaj źródło do pliku wykonywalnego tego projektu.
add_executable (Snake3D "main.cpp" ${GLAD_SOURCE_FILES} ${ENGINE_SOURCE_FILES}  ${STB_SOURCE_FILES}  ${GLFW_SOURCE_FILES}  ${SNAKE_IMPLEMENTATION} )

target_link_libraries( Snake3D PRIVATE glfw )
target_link_libraries( Snake3D PRIVATE glad )
target_link_libraries( Snake3D PRIVATE freetype )
target_link_libraries( Snake3D PRIVATE assimp )
target_link_libraries( Snake3D PRIVATE ${IRRKLANG_LIB})

# copy .dll irrklang files
if (WIN32)
    add_custom_command(TARGET Snake3D POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${IRRKLANG_DIR}/bin/irrKlang.dll
            $<TARGET_FILE_DIR:Snake3D>
        COMMAND ${CMAKE_COMMAND} -E copy
            ${IRRKLANG_DIR}/bin/ikpMP3.dll
            $<TARGET_FILE_DIR:Snake3D>
        COMMAND ${CMAKE_COMMAND} -E copy
            ${IRRKLANG_DIR}/bin/ikpFlac.dll
            $<TARGET_FILE_DIR:Snake3D>
    )
endif()



# copy resources to executable path
set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/Snake3D/resources)

add_custom_command(TARGET Snake3D POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_DIR}
    $<TARGET_FILE_DIR:Snake3D>/resources
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Snake3D PROPERTY CXX_STANDARD 14)
endif()


