//
// Created by Henry Little on 2019/9/15.
//

#include "TerrainGenerator.hpp"
unsigned char* TerrainGenerator::createMeshData(float *heights, glm::i8vec4 *color, int width, int height, int vertexCount) {
    unsigned int byteCount = vertexCount * BYTES_PER_VERTEX;
    buffer = new ByteBuffer(byteCount);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

        }
    }
}