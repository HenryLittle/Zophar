//
// Created by Henry Little on 2019-09-12.
//

#ifndef RENDERENGINE_BOX_HPP
#define RENDERENGINE_BOX_HPP


#include "../../OpenGLWrapper/Shader.hpp"
#include "../../OpenGLWrapper/Texture.hpp"
#include "../Renderable.hpp"

class Box : public Renderable{
public:
    Box();
    void render() override;
private:
    static float vertices[];
    static unsigned int indices[];
    static glm::vec3 cubePositions[];
    Shader* shader;
    unsigned int VAO;
    unsigned int VBO;
    Texture* texture1;
    Texture* texture2;
    void prepare();
};


#endif //RENDERENGINE_BOX_HPP
