//
// Created by Henry Little on 2019-06-12.
//

#include "InputManager.hpp"
#include "../SolarSystem/CelestialBody.hpp"

// Global static pointer used to ensure a single instance of the class

InputManager *InputManager::Instance() {
    static InputManager(input);
    return &input;
}

void InputManager::registerCallback(GLFWwindow *window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    // enable unlimited mouse movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    if (InputManager::Instance()->isFirstMouse) {
        InputManager::Instance()->xPosCurPrev = xpos;
        InputManager::Instance()->yPosCurPrev = ypos;
        InputManager::Instance()->isFirstMouse = false;
    }
    // process camera
    if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED && Context::Instance().camera) {
        if (const auto &eCam = dynamic_cast<EularCamera *>(Context::Instance().camera)) {
            eCam->processMouseInput(
                    (float) xpos - InputManager::Instance()->xPosCurPrev,
                    (float) ypos - InputManager::Instance()->yPosCurPrev);

        }
    }
    InputManager::Instance()->xPosCurPrev = (float) xpos;
    InputManager::Instance()->yPosCurPrev = (float) ypos;

}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    std::cout << "no" << std::endl;
    if (button == GLFW_MOUSE_BUTTON_LEFT && glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    Context::Instance().windowManager->updateWindowSize(width, height);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
//    std::cout<<"xoffset: "<< xoffset << "yoffset: "<<yoffset<<std::endl;
    if (Context::Instance().camera) {
        if (const auto &cam = dynamic_cast<EularCamera *>(Context::Instance().camera)) {
            cam->processMouseScroll(yoffset);
        }
    }
}

void cursor_enter_callback(GLFWwindow *window, int entered) {

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        Context::Instance().wireFrame = !Context::Instance().wireFrame;
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
        CelestialBody::pause = !CelestialBody::pause;
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
        CelestialBody::showOrbit = !CelestialBody::showOrbit;
    if (key == GLFW_KEY_LEFT_BRACKET && action == GLFW_PRESS)
        CelestialBody::timeScaleFactor /= 2.0f;
    if (key == GLFW_KEY_RIGHT_BRACKET && action == GLFW_PRESS)
        CelestialBody::timeScaleFactor *= 2.0f;
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
        Context::Instance().ctLight = !Context::Instance().ctLight;
}
