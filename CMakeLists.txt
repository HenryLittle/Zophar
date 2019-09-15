cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME RenderEngine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
# might be system specific
set(SYS_INCLUDE /usr/local/include/)
set(PROJECT_INCLUDE ./include)
# add to headers
include_directories(${SYS_INCLUDE} ${PROJECT_INCLUDE})
set(GLEW_LINK /usr/local/lib/libGLEW.2.1.dylib)
set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)

link_libraries(${OPENGL} ${GLEW_LINK} ${GLFW_LINK})

file(GLOB SOURCE_FILES
        "testEngine.cpp"
        "*.hpp"
        "include/*"
        "lib/*.c"
        "RenderEngine/*.cpp"
        "RenderEngine/Box/*.cpp"
        "RenderEngine/Context/*.cpp"
        "RenderEngine/WindowManager/*.cpp"
        "RenderEngine/InputManager/*.cpp"
        "RenderEngine/Camera/*.cpp"
        "OpenGLWrapper/*.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} RenderEngine/Terrain/PerlinNoise.cpp RenderEngine/Terrain/PerlinNoise.hpp RenderEngine/Terrain/TerrainGenerator.cpp RenderEngine/Terrain/TerrainGenerator.hpp RenderEngine/Utils/ByteBuffer.cpp RenderEngine/Utils/ByteBuffer.hpp RenderEngine/Terrain/Square.cpp RenderEngine/Terrain/Square.hpp)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()