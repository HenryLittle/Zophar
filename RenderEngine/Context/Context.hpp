//
// Created by Henry Little on 2019-09-11.
//

#ifndef RENDERENGINE_CONTEXT_HPP
#define RENDERENGINE_CONTEXT_HPP

#include "../WindowManager/WindowManager.hpp"
#include "../Camera/AbstractCamera.hpp"

/* A singleton object that contains all the references in the pipeline */

class Context {
public:
    static Context& Instance();
    WindowManager* windowManager = nullptr;
    AbstractCamera* camera;
    int width, height;
private:

};


#endif //RENDERENGINE_CONTEXT_HPP
