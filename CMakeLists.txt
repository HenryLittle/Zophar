cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME RenderEngine)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${OPENGL} ${GLEW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    link_libraries(${OPENGL_LIBRARY})
endif()

# might be system specific
set(SYS_INCLUDE /usr/local/include/)
set(PROJECT_INCLUDE ./include)
# add to headers
include_directories(${SYS_INCLUDE} ${PROJECT_INCLUDE} ${OPENGL_INCLUDE_DIRS})


# set(GLEW_LINK /usr/local/lib/libGLEW.2.1.dylib)
# set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)

# link_libraries(${OPENGL})

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
else()
    target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES} "-ldl")
endif()