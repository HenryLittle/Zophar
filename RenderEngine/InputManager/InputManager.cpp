//
// Created by Henry Little on 2019-06-12.
//

#include "InputManager.hpp"
#include "../Context/Context.hpp"

// Global static pointer used to ensure a single instance of the class

InputManager *InputManager::Instance() {
    static InputManager(input);
    return &input;
}

void InputManager::registerCallback(GLFWwindow *window) {
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    if (InputManager::Instance()->isFirstMouse) {
        InputManager::Instance()->xPosCurPrev = xpos;
        InputManager::Instance()->yPosCurPrev = ypos;
        InputManager::Instance()->isFirstMouse = false;
    }
    // process camera
    if (Context::Instance().camera) {
        if (const auto& eCam = dynamic_cast<EularCamera*>(Context::Instance().camera)) {
            eCam->processMouseInput(
                    (float)xpos - InputManager::Instance()->xPosCurPrev,
                    (float)ypos - InputManager::Instance()->yPosCurPrev);
        }
        InputManager::Instance()->xPosCurPrev = (float)xpos;
        InputManager::Instance()->yPosCurPrev = (float)ypos;
    }

}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    std::cout << "no" << std::endl;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    Context::Instance().windowManager->updateWindowSize(width, height);
}
