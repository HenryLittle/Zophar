//
// Created by Henry Little on 2019-09-11.
//

#include "RenderEngine.hpp"

std::vector<RenderablePtr> RenderEngine::renderList;

RenderEngine::RenderEngine(int width, int height) {
    // set up the glfw window
    context.windowManager = new WindowManager(width, height);
    // 直接从 GLFW 获取宽高
    glfwGetFramebufferSize(context.windowManager->getWindow(), &frameWidth, &frameHeight);
    // tell GL the positions
    // (0, 1)left down conner | (2)width | (3)height
    glViewport(0, 0, frameWidth, frameHeight);
}

void RenderEngine::add(RenderablePtr renderable) {
    RenderEngine::renderList.emplace_back(renderable);
}

// prepare for a render pass
void RenderEngine::prepare() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::render() {
    prepare();
    for (auto& r: RenderEngine::renderList) {
        r->render();
    }
}

void RenderEngine::addCamera(AbstractCamera *camera) {
    context.camera = camera;
}