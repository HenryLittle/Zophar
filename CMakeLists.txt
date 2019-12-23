cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME Solar)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
    # Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
    link_directories(/usr/local/lib)
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
if (GLFW_FOUND)
    include_directories(${GLFW_INCLUDE_DIRS})
    link_libraries(${GLFW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)

    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARY})
endif()

find_package(ASSIMP REQUIRED)
if (ASSIMP_FOUND)
    message(INFO "Assimp found at " ${ASSIMP_LIBRARIES} )
    include_directories(${ASSIMP_INCLUDE_DIRS})
    link_libraries(${ASSIMP_LIBRARIES})
endif()

# might be system specific
set(SYS_INCLUDE /usr/local/include/)
set(PROJECT_INCLUDE ./include)
# add to headers
include_directories(${SYS_INCLUDE} ${PROJECT_INCLUDE})


# set(GLEW_LINK /usr/local/lib/libGLEW.2.1.dylib)
#if (APPLE)
#    set(GLFW_LINK /usr/local/lib/libglfw.3.dylib)
#    link_libraries(${GLFW_LINK})
#endif ()

file(GLOB SOURCE_FILES
        "testEngine.cpp"
        "*.hpp"
        "include/*"
        "lib/*.c"
        "RenderEngine/*.cpp"
#        "RenderEngine/Box/*.cpp"
        "RenderEngine/Context/*.cpp"
        "RenderEngine/WindowManager/*.cpp"
        "RenderEngine/InputManager/*.cpp"
        "RenderEngine/Camera/*.cpp"
        "OpenGLWrapper/Shader.cpp"
        "RenderEngine/ObjectModel/Model.hpp"
        "RenderEngine/SolarSystem/*.cpp"
        "RenderEngine/ObjectModel/Model.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES} RenderEngine/SkyBox/SkyBox.cpp RenderEngine/SkyBox/SkyBox.h)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
else()
    target_link_libraries(${PROJECT_NAME} "-ldl")
endif()