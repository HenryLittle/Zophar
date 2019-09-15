#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "RenderEngine/Box/Box.hpp"
#include "RenderEngine/RenderEngine.hpp"
#include "RenderEngine/Camera/EularCamera.hpp"
#include "RenderEngine/InputManager/InputManager.hpp"
#include "RenderEngine/Terrain/PerlinNoise.hpp"

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间


void processInput(GLFWwindow *window) {
    if (auto camera = dynamic_cast<EularCamera*>(Context::Instance().camera)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->processKeyInput(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->processKeyInput(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->processKeyInput(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->processKeyInput(RIGHT, deltaTime);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    // initialize the render engine and its context
    auto renderEngine = new RenderEngine(800, 600);
    // add objects to render
    renderEngine->add(std::make_shared<Box>());
    // add a camera to the render engine
    auto camera = new EularCamera();
    renderEngine->addCamera(camera);
    // register the input manager
    InputManager::Instance()->registerCallback(Context::Instance().windowManager->getWindow());

    PerlinNoise perlin = PerlinNoise(237);
    for (int i = 0; i < 100; i ++) {
        for (int j = 0; j < 100; j ++) {
            if (j != 0) {
                std::cout << " ";
            }
            std::cout << perlin.noise((double)i / 8.0, (double)j / 8.0, 0);
        }
        std::cout << std::endl;
    }

    while (!glfwWindowShouldClose(Context::Instance().windowManager->getWindow())) {
        // should be managed by the engine
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(Context::Instance().windowManager->getWindow());

        // ask the engine to render the scene
        renderEngine->render();
        // should be managed by the engine or its sub_modules
        // poll & swap buffer
        glfwPollEvents();
        glfwSwapBuffers(Context::Instance().windowManager->getWindow());
    }

    glfwTerminate();
    return 0;
}


