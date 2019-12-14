//
// Created by Henry Little on 2019/9/15.
//

#ifndef RENDERENGINE_BYTEBUFFER_HPP
#define RENDERENGINE_BYTEBUFFER_HPP


class ByteBuffer {
public:
    ByteBuffer(unsigned int byteCount);
    void write(void* src, unsigned int size);
    unsigned char* getByteArray();
private:
    unsigned int offset = 0;
    unsigned int bufferSize;
    unsigned char* buffer;
};


#endif //RENDERENGINE_BYTEBUFFER_HPP
