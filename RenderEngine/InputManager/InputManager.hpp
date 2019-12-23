//
// Created by Henry Little on 2019-06-12.
//


#ifndef RENDERENGINE_INPUTMANAGER_HPP
#define RENDERENGINE_INPUTMANAGER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Camera/EularCamera.h"
//#include "../SolarSystem/CelestialBody.hpp"


class InputManager {
public:

    static InputManager* Instance();
    void registerCallback(GLFWwindow *window);

    float xPosCurPrev = 0;
    float yPosCurPrev = 0;
    bool isFirstMouse = true;

private:
};

using InputManagerPtr = std::shared_ptr<InputManager>;

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

static void cursor_enter_callback(GLFWwindow* window, int entered);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif //RENDERENGINE_INPUTMANAGER_HPP

