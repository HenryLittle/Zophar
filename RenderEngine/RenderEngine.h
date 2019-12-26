//
// Created by Henry Little on 2019-09-11.
//

#ifndef RENDERENGINE_RENDERENGINE_HPP
#define RENDERENGINE_RENDERENGINE_HPP

#include <vector>
#include "Context/Context.h"
#include "Renderable.h"
#include "Camera/AbstractCamera.h"
#include "Camera/EularCamera.h"

/* The render engine is responsible for manage the render pipeline for each frame
 *  and manage the window & input
 */

class RenderEngine {
public:
    RenderEngine(int width, int height);
    int frameHeight, frameWidth;
    void render();
    void add(RenderablePtr renderable);
    void addCamera(AbstractCamera* camera);
    // may want to access it from other render method
    static std::vector<RenderablePtr> renderList;
private:
    Context& context = Context::Instance();
    void prepare();
};


#endif //RENDERENGINE_RENDERENGINE_HPP
