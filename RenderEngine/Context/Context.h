//
// Created by Henry Little on 2019-09-11.
//

#ifndef RENDERENGINE_CONTEXT_HPP
#define RENDERENGINE_CONTEXT_HPP

#include "../WindowManager/WindowManager.h"
#include "../Camera/AbstractCamera.h"
/* A singleton object that contains all the references in the pipeline */

class Context {
public:
    static Context& Instance();
    WindowManager* windowManager = nullptr;
    AbstractCamera* camera = nullptr;
    // render information
    int width, height;
    bool wireFrame = false;
    // control config
    bool invertXY = false;
    bool ctLight = true;
private:

};


#endif //RENDERENGINE_CONTEXT_HPP
