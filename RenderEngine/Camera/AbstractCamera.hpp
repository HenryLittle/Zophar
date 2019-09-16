//
// Created by Henry Little on 2019-09-12.
//

#ifndef RENDERENGINE_ABSTRACTCAMERA_HPP
#define RENDERENGINE_ABSTRACTCAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class AbstractCamera{
public:
    virtual glm::mat4 getPerspectiveMat() = 0;
    virtual glm::mat4 getViewMat() = 0;
};

#endif //RENDERENGINE_ABSTRACTCAMERA_HPP
