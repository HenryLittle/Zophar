//
// Created by Henry Little on 2019-09-12.
//
#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"


Texture::Texture(const char *texturePath) {
    path = texturePath;
    glGenTextures(1, &ID);// param: number of textures, id
    glBindTexture(texture_target, ID);// bind the texture object
}

void Texture::load() {
    // set the texture wrapping parameters
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_S, wrap_s);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(texture_target, GL_TEXTURE_WRAP_T, wrap_t);
    // set texture filtering parameters
    glTexParameteri(texture_target, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(texture_target, GL_TEXTURE_MAG_FILTER, mag_filter);
    int img_width, img_height, img_channel;
    unsigned char *data = stbi_load(path, &img_width, &img_height, &img_channel, 0);
    if (data) {
        // the 6th parameter is always 0 for historical reasons (border)
        glTexImage2D(texture_target, 0, internal_format, img_width, img_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(ID);
    } else {
        std::cout << "ERROR::TEXTURE::Failed to load texture: " << path << std::endl;
    }
    // free after complete Texture & Mipmap generation
    stbi_image_free(data);
}

void Texture::use() {
    glBindTexture(texture_target, ID);
}
