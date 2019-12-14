//
// Created by Henry Little on 2019-09-12.
//

#ifndef RENDERENGINE_EULARCAMERA_HPP
#define RENDERENGINE_EULARCAMERA_HPP

#include <memory>
#include "AbstractCamera.hpp"
#include "../Context/Context.hpp"

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

    EularCamera(glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f),
                float mYaw = YAW, float mPitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED),
                                                          mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
        position = mPosition;
        worldUp = mUp;
        yaw = mYaw;
        pitch = mPitch;
        updateCameraVectors();
    }

    glm::mat4 getPerspectiveMat() override {
        return glm::perspective(glm::radians(zoom),
                                (float) Context::Instance().width / (float) Context::Instance().height, 0.1f, 100.0f);
    };

    glm::mat4 getViewMat() override {
        return glm::lookAt(position, position + front, up);
    };

    glm::vec3 getEyePosition() override {
        return this->position;
    }

    void processMouseInput(float offsetX, float offsetY, bool constraint = true) {
        offsetX *= mouseSensitivity * (zoom / 45.0f);
        offsetY *= mouseSensitivity * (zoom / 45.0f);
        if (Context::Instance().invertXY) {
            yaw -= offsetX;
            pitch += offsetY;
        } else {
            yaw += offsetX;
            pitch -= offsetY;
        }

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constraint) {
            if (pitch > 89.0f)
                pitch = 89.0f;
            if (pitch < -89.0f)
                pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    };


    void processKeyInput(CameraMove move, float deltaTime) {
        float offset = movementSpeed * deltaTime;
        if (move == FORWARD)
            position += front * offset;
        if (move == BACKWARD)
            position -= front * offset;
        if (move == LEFT)
            position -= right * offset;
        if (move == RIGHT)
            position += right * offset;
        if (move == UP)
            position += worldUp * offset;
        if (move == DOWN)
            position -= worldUp * offset;
    };

    void processMouseScroll(float offset) {
        // TODO: a better zoom handling
        if (zoom >= 1.0f && zoom <= 45.0f)
            zoom -= offset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 45.0f)
            zoom = 45.0f;
    }

private:

    // calculate the normalized cam vectors from yaw and pitch angles (!potential lock)
    void updateCameraVectors() {
        glm::vec3 tFront;
        tFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        tFront.y = sin(glm::radians(pitch));
        tFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(tFront);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    };
};


#endif //RENDERENGINE_EULARCAMERA_HPP
