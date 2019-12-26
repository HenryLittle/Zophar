//
// Created by Henry Little on 2019-09-11.
//

#include "WindowManager.h"
#include "../Context/Context.h"

WindowManager::WindowManager(int width, int height) {
    // 初始化 GLFW
    glfwInit();
    // use glfwWindowHint to configure glfw
    // 告诉 GLFW 我们使用的OpenGL版本号 MAJOR-主版本号，MINOR-次版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
    // use openGL core mode
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
    // Specific for Mac
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // 创建窗口
    window = glfwCreateWindow(width, height, WINDOW_NAME.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Create GLFW window failed" << std::endl;
        glfwTerminate();
    } else {
        updateWindowSize(width, height);
        // 上下文设置为此窗口
        glfwMakeContextCurrent(window);
        // initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
    }
}

GLFWwindow* WindowManager::getWindow() {
    return window;
}

WindowManager::~WindowManager() {
    // clean up for window
}

void WindowManager::updateWindowSize(int width, int height) {
    Context::Instance().width = width;
    Context::Instance().height = height;
}