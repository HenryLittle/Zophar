//
// Created by Henry Little on 2019-09-11.
//

#ifndef RENDERENGINE_WINDOWMANAGER_HPP
#define RENDERENGINE_WINDOWMANAGER_HPP


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../EngineConfig.h"

class WindowManager {
public:
    WindowManager(int width, int height);
    static void updateWindowSize(int width, int height);
    GLFWwindow* getWindow();
    ~WindowManager();
private:
    GLFWwindow* window;
};


#endif //RENDERENGINE_WINDOWMANAGER_HPP
