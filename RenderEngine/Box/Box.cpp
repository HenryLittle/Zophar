//
// Created by Henry Little on 2019-09-12.
//


#include "Box.hpp"

#include "../Renderable.hpp"
#include "../Context/Context.hpp"

float Box::vertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.5,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // 左上
        0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,   // back右上
        0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // back右下
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,   // back左下
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   1.0f, 1.0f    // back左上
};

unsigned int Box::indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
        0, 1, 5,
        0, 4, 5,
        0, 3, 4,
        3, 4, 7,
        2, 6, 3,
        6, 7, 3,
        2, 1, 5,
        2, 5, 6,
        6, 4, 7,
        6, 5, 4
};

glm::vec3 Box::cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

Box::Box() {
    shader = new Shader("../shaders/vShader.glsl", "../shaders/fShader.glsl");

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Box::indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // vaos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    // set the Shape Assembly Mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* load and generate a Texture form image */
    texture1 = new Texture("../res/container.jpg");
    texture1->load();
    texture2 = new Texture("../res/awesomeface.png");
    texture2->internal_format = GL_RGBA;
    texture2->format = GL_RGBA;
    texture2->load();
    // set the uniform
    // shader.activate();
    // glUniform1i(glGetUniformLocation(shader.ID, "texture"), 0); or
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    shader->activate(); // make sure to activate the shader before use
    shader->setInt("texture1", 0); // name of the uniform do not confuse
    shader->setInt("texture2", 1);
}

void Box::prepare() {
    glEnable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0); // activate the texture unit
    texture1->use();
    glActiveTexture(GL_TEXTURE1);
    texture2->use();

    shader->activate();
}

void Box::render() {
    prepare();
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;

    if (Context::Instance().camera) {
        projection = Context::Instance().camera->getPerspectiveMat();
        view = Context::Instance().camera->getViewMat();
    }
    // projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * (i + 1);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
        shader->activate();
        shader->setMat4("model", model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    }
}