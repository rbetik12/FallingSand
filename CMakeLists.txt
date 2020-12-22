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
add_subdirectory(lib/vx-sound)
add_subdirectory(lib/Nuklear)

include_directories(lib/glad/include)
include_directories(lib/vx-sound/include)
include_directories(lib)
include_directories(lib/Nuklear)
add_executable(falling_sand src/Main.c src/utils/Config.h src/game/Game.h src/game/Game.c src/opengl/VertexArray.h src/opengl/VertexArray.c src/opengl/Buffer.h src/opengl/Buffer.c src/utils/Debug.h src/utils/Debug.c src/opengl/Shader.h src/opengl/Shader.c src/game/Gamefield.h src/game/Gamefield.c src/game/Color32.h src/game/Pixel.h src/game/PixelType.h lib/stb/stb_image.h src/utils/ImageLoader.h src/utils/ImageLoader.c src/utils/Input.h src/utils/Input.c src/game/Simulation.h src/game/Simulation.c src/utils/AudioManager.c src/utils/AudioManager.h)

if (UNIX)
    set_target_properties(falling_sand PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    set_target_properties(falling_sand PROPERTIES INSTALL_RPATH "./lib")
endif()

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Qunused-arguments")
endif()

set(LIBS nuklear glad vortex_sound glfw)
if (UNIX)
    target_link_libraries(falling_sand ${LIBS} GL GLU dl X11 Xxf86vm Xrandr pthread Xi Xinerama Xcursor)
elseif (WIN32)
    target_link_libraries(falling_sand ${LIBS} GLU32 opengl32)
endif()