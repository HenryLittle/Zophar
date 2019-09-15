//
// Created by Henry Little on 2019-09-11.
//

#ifndef RENDERENGINE_WINDOWMANAGER_HPP
#define RENDERENGINE_WINDOWMANAGER_HPP

#include <GLFW/glfw3.h>
#include <iostream>

#include "../EngineConfig.hpp"

class WindowManager {
public:
    WindowManager(int width, int height);
    void updateWindowSize(int width, int height);
    GLFWwindow* getWindow();
    ~WindowManager();
private:
    GLFWwindow* window;
};


#endif //RENDERENGINE_WINDOWMANAGER_HPP