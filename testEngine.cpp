#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//#include "RenderEngine/Box/Box.hpp"
#include "RenderEngine/RenderEngine.hpp"
#include "RenderEngine/Camera/EularCamera.hpp"
#include "RenderEngine/InputManager/InputManager.hpp"
#include "OpenGLWrapper/Shader.h"
#include "RenderEngine/SolarSystem/CelestialBody.hpp"
#include "RenderEngine/SkyBox/SkyBox.h"

#define RADIAN(a) ((a)/180.0f * 3.141596)

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

void processInput(GLFWwindow *window) {
    if (auto camera = dynamic_cast<EularCamera *>(Context::Instance().camera)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            //glfwSetWindowShouldClose(window, true);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->processKeyInput(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->processKeyInput(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->processKeyInput(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->processKeyInput(RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            camera->processKeyInput(UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera->processKeyInput(DOWN, deltaTime);
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    // initialize the render engine and its context
    auto renderEngine = new RenderEngine(800, 600);
    // add objects to render
//    renderEngine->add(std::make_shared<Box>());
    // add a camera to the render engine
    auto camera = new EularCamera();
    renderEngine->addCamera(camera);
    // register the input manager
    InputManager::Instance()->registerCallback(Context::Instance().windowManager->getWindow());

    // try to load the nano suit
    Shader cookTorranceShader = Shader(
            "cookTorrance.v.glsl",
            "cookTorrance.f.glsl");

    Shader phongShader = Shader(
            "phong.v.glsl",
            "phong.f.glsl");

    Shader sunShader = Shader(
            "sun.v.glsl",
            "sun.f.glsl");

    Shader skyBoxShader = Shader(
            "skybox/skybox.v.glsl",
            "skybox/skybox.f.glsl"
            );

    auto skyBox = SkyBox("../texture/defaultSky/", "jpg");
    auto galaxyCoreBox = SkyBox("../texture/GalaxyCore/", "png");
    auto crabNebulaBox = SkyBox("../texture/CrabNebula/", "png");
    auto darkGalaxyBox = SkyBox("../texture/DarkGalaxy/", "png");
    auto *sun = new CelestialBody("sun", 2.40f);
    sun->rotationAngleSpeed = 0.040f;

    // angle relative to sun plane | body radius relative to earth | orbit in AU
    auto *mercury = new CelestialBody(
            "mercury",
            0.16f,
            2.8f,
            RADIAN(3.38f),
            RADIAN(2.18f),
            0.017f,
            1.149f
    );
    mercury->setCenterBody(sun);


    auto *venus = new CelestialBody(
            "venus",
            0.4f,
            4.5f,
            RADIAN(3.39f),
            RADIAN(2.64f),
            -0.004f,
            0.446f
    );
    venus->setCenterBody(sun);


    auto *earth = new CelestialBody(
            "earth",
            0.42f,
            6.0f,
            RADIAN(7.155f),
            RADIAN(23.439f),
            1.0f,
            0.274f
    );
    earth->setCenterBody(sun);


    auto *moon = new CelestialBody(
            "moon",
            0.1f,
            0.8f,
            RADIAN(18.29f),
            RADIAN(6.687f),
            0.957f,
            2.7f
    );
    moon->setCenterBody(earth);


    auto *mars = new CelestialBody(
            "mars",
            0.23f,
            8.0f,
            RADIAN(5.65f),
            RADIAN(25.19f),
            0.975f,
            0.146f
    );
    mars->setCenterBody(sun);

    auto *jupiter = new CelestialBody(
            "jupiter",
            1.56f,
            11.0f,
            RADIAN(1.305f),
            RADIAN(3.13f),
            2.632f,
            0.023f
    );
    jupiter->setCenterBody(sun);


    auto *saturn = new CelestialBody(
            "saturn",
            1.02f,
            15.0f,
            RADIAN(2.485f),
            RADIAN(26.73f),
            2.222f,
            0.009f
    );
    saturn->setCenterBody(sun);


    auto *uranus = new CelestialBody(
            "uranus",
            1.70f,
            19.0f,
            RADIAN(0.772f),
            RADIAN(97.77f),
            1.408f,
            0.003f
    );
    uranus->setCenterBody(sun);

    auto *neptune = new CelestialBody(
            "neptune",
            1.64f,
            32.0f,
            RADIAN(1.767f),
            RADIAN(28.32f),
            1.266f,
            0.002f
    );
    neptune->setCenterBody(sun);


    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    phongShader.setVec3("lightPos", lightPos);
    cookTorranceShader.setVec3("lightPos", lightPos);

    std::cout << "OpenGL Version is: " << glGetString(GL_VERSION) << std::endl;

    while (!glfwWindowShouldClose(Context::Instance().windowManager->getWindow())) {
        // should be managed by the engine
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(Context::Instance().windowManager->getWindow());

        // ask the engine to render the scene
        renderEngine->render();

        glEnable(GL_DEPTH_TEST);
        if (Context::Instance().wireFrame) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        auto view = Context::Instance().camera->getViewMat();
        auto perspective = Context::Instance().camera->getPerspectiveMat();
        auto eyePosition = Context::Instance().camera->getEyePosition();
        phongShader.setMat4("view", view);
        phongShader.setMat4("projection", perspective);
        phongShader.setVec3("eyePos", eyePosition);
        cookTorranceShader.setMat4("view", view);
        cookTorranceShader.setMat4("projection", perspective);
        cookTorranceShader.setVec3("eyePos", eyePosition);
        sunShader.setMat4("view", view);
        sunShader.setMat4("projection", perspective);

        // render the celestial objects
        sun->render(sunShader);
        if (Context::Instance().ctLight) {
            mercury->render(cookTorranceShader);
            venus->render(cookTorranceShader);
            earth->render(cookTorranceShader);
            moon->render(cookTorranceShader);
            mars->render(cookTorranceShader);
            jupiter->render(cookTorranceShader);
            saturn->render(cookTorranceShader);
            uranus->render(cookTorranceShader);
            neptune->render(cookTorranceShader);
        } else {
            mercury->render(phongShader);
            venus->render(phongShader);
            earth->render(phongShader);
            moon->render(phongShader);
            mars->render(phongShader);
            jupiter->render(phongShader);
            saturn->render(phongShader);
            uranus->render(phongShader);
            neptune->render(phongShader);
        }


        auto clippedView = glm::mat4(glm::mat3(view));
        skyBoxShader.setMat4("view", clippedView);
        skyBoxShader.setMat4("projection", perspective);
//        skyBox.render(skyBoxShader);
//        galaxyCoreBox.render(skyBoxShader);
        //crabNebulaBox.render(skyBoxShader);
        darkGalaxyBox.render(skyBoxShader);
        // should be managed by the engine or its sub_modules
        // poll & swap buffer
        glfwPollEvents();
        glfwSwapBuffers(Context::Instance().windowManager->getWindow());
    }

    glfwTerminate();
    return 0;
}


