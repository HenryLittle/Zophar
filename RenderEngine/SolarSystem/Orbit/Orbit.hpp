//
// Created by Henry Little on 2019/10/15.
//

#ifndef RENDERENGINE_ORBIT_HPP
#define RENDERENGINE_ORBIT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../../OpenGLWrapper/Shader.h"
#include "../../Context/Context.hpp"


#include <cmath>
const float STEP = 1.0f;
const float PI = 3.141592;
class Orbit{
public:
    glm::mat4 model = glm::mat4(1.0);
    Shader* shader;
    unsigned int VAO, VBO;
    float* vertices;
    int count;
    Orbit(){
        shader = new Shader("../shaders/vShader.glsl", "../shaders/fShader.glsl");
        calculateVertices();

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);
        //std::cout << sizeof(vertices) << std::endl;
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
        glEnableVertexAttribArray(0);
    };

    void setModel(glm::mat4 mModel){
        model = mModel;
    };

    // prepare shaders
    void prepare(){
        glEnable(GL_DEPTH_TEST);
        shader->activate();
    };

    void render(){
        prepare();
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection;

        if (Context::Instance().camera) {
            projection = Context::Instance().camera->getPerspectiveMat();
            view = Context::Instance().camera->getViewMat();
        }
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        shader->setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_LOOP, 0, count);
    };

private:
    void calculateVertices(){
        count = (int)(360.0f / STEP);
        vertices = new float[count * 3];
        for (int i = 0; i < count; i++ ) {
            vertices[3 * i + 0] = (float)cos(PI * (float)i * STEP / 180.0f) * 1.0f; // x
            vertices[3 * i + 1] = 0.0f; // y
            vertices[3 * i + 2] = (float)sin(PI * (float)i * STEP / 180.0f) * 1.0f; // z
        }
        std::cout << count * 3 << std::endl;
    }
};

#endif //RENDERENGINE_ORBIT_HPP
