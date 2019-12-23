//
// Created by Henry Little on 2019-09-12.
//

#ifndef RENDERENGINE_RENDERABLE_HPP
#define RENDERENGINE_RENDERABLE_HPP

#include <memory>

class Renderable{
public:
    virtual void render() = 0;
};
using RenderablePtr = std::shared_ptr<Renderable>;

#endif //RENDERENGINE_RENDERABLE_HPP