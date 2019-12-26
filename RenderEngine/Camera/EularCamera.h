//
// Created by Henry Little on 2019-09-12.
//

#ifndef RENDERENGINE_EULARCAMERA_HPP
#define RENDERENGINE_EULARCAMERA_HPP

#include <memory>
#include "AbstractCamera.h"
#include "../Context/Context.h"

enum CameraMove {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class EularCamera : public AbstractCamera {

public:
    // Camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up; // up for the camera
    glm::vec3 right;
    glm::vec3 worldUp; // the world's up direction
    // Euler Angles
    float yaw;
    float pitch;
    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    EularCamera(glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 0.0f), 
                glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f),
                float mYaw = YAW, 
                float mPitch = PITCH
            ) ;

    glm::mat4 getPerspectiveMat() override;
    glm::vec3 getEyePosition() override;
    glm::mat4 getViewMat() override;

    void processMouseInput(float offsetX, float offsetY, bool constraint = true);
    void processKeyInput(CameraMove move, float deltaTime);
    void processMouseScroll(float offset);

    

private:
    // calculate the normalized cam vectors from yaw and pitch angles (!potential lock)
    void updateCameraVectors();
};


#endif //RENDERENGINE_EULARCAMERA_HPP
