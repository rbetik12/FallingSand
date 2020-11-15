cmake_minimum_required(VERSION 3.17)
project(falling_sand C)

set(CMAKE_C_STANDARD 11)

if (UNIX)
        set(PLATFORM Linux)
elseif (WIN32)
        set(PLATFORM Windows)
endif()

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE}-${PLATFORM}/${CMAKE_PROJECT_NAME})

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)

include_directories(lib/glad/include)
include_directories(lib)
add_executable(falling_sand src/Main.c src/utils/Config.h src/game/Game.h src/game/Game.c src/opengl/VertexArray.h src/opengl/VertexArray.c src/opengl/Buffer.h src/opengl/Buffer.c src/utils/Debug.h src/utils/Debug.c src/opengl/Shader.h src/opengl/Shader.c src/game/Gamefield.h src/game/Gamefield.c src/game/Color32.h src/game/Pixel.h src/game/PixelType.h lib/stb/stb_image.h src/utils/ImageLoader.h src/utils/ImageLoader.c src/utils/Input.h src/utils/Input.c)

target_link_libraries(falling_sand glad GL GLU glfw dl X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor)