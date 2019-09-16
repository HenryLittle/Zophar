//
// Created by Henry Little on 2019/9/15.
//

#ifndef RENDERENGINE_TERRAINGENERATOR_HPP
#define RENDERENGINE_TERRAINGENERATOR_HPP


#include <glm/fwd.hpp>
#include "../Utils/ByteBuffer.hpp"

class TerrainGenerator {
    // the normal is compressed using the technique described here:
    // https://paroj.github.io/gltut/Basic%20Optimization.html
    const static int BYTES_PER_VERTEX = 20; // 12[position] + 4[normal] + 4[color]
public:
    unsigned char* createMeshData(float* heights, glm::i8vec4* color, int width, int height, int vertexCount);

private:
    ByteBuffer* buffer;
};


#endif //RENDERENGINE_TERRAINGENERATOR_HPP
