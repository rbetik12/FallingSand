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
add_executable(falling_sand src/Main.c src/Config.h src/Game.h src/Game.c src/VertexArray.h src/VertexArray.c src/Buffer.h src/Buffer.c src/Debug.h src/Debug.c src/Shader.h src/Shader.c)

target_link_libraries(falling_sand glad GL GLU glfw dl X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor)