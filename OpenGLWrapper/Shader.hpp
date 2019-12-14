//
// Created by Henry Little on 2019-06-06.
//

#ifndef RENDERENGINE_SHADER_HPP
#define RENDERENGINE_SHADER_HPP


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
public:
    unsigned ID;
    Shader (const char * vertexPath, const char * fragmentPath);
    void activate();
    // uniform tools
    void setBool(const std::string &name, bool value) const; // const -> do not change *this
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 mat4, GLenum transpose = GL_FALSE) const;
    void setVec3(const std::string &name, glm::vec3 vec3) const;
private:
    static void checkCompileErr(unsigned int shader, const std::string& type);
};



#endif //RENDERENGINE_SHADER_HPP
