//
// Created by Henry Little on 2019-06-12.
//


#ifndef OH_KAMI_INPUTMANAGER_HPP
#define OH_KAMI_INPUTMANAGER_HPP

#include <GLFW/glfw3.h>
#include <iostream>
#include "../Camera/EularCamera.hpp"



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

#endif //OH_KAMI_INPUTMANAGER_HPP

