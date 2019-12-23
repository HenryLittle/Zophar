//
// Created by Henry Little on 2019/12/14.
//

#ifndef SOLAR_SKYBOX_H
#define SOLAR_SKYBOX_H

#include <vector>
#include "../../OpenGLWrapper/Shader.h"

class SkyBox {
public:
    static float vertices[];
    explicit SkyBox(std::vector<std::string> faces);
    SkyBox(std::string path, std::string format);
    void render(Shader shader);

private:
    unsigned int VAO, VBO;
    unsigned int textureID;
    void loadTextureMap(std::vector<std::string> faces);
    void initializeObjects();
};


#endif //SOLAR_SKYBOX_H
