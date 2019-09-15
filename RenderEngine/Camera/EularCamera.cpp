//
// Created by Henry Little on 2019-09-12.
//

#include "EularCamera.hpp"
#include "../Context/Context.hpp"

glm::mat4 EularCamera::getViewMat() {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 EularCamera::getPerspectiveMat() {
    return glm::perspective(glm::radians(45.0f), (float)Context::Instance().width / (float)Context::Instance().height, 0.1f, 100.0f);
}

// calculate the normalized cam vectors from yaw and pitch angles (!potential lock)
void EularCamera::updateCameraVectors() {
    glm::vec3 tFront;
    tFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tFront.y = sin(glm::radians(pitch));
    tFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(tFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void EularCamera::processKeyInput(CameraMove direction, float deltaTime) {
    float offset = movementSpeed * deltaTime;
    if (direction == FORWARD)
        position += front * offset;
    if (direction == BACKWARD)
        position -= front * offset;
    if (direction == LEFT)
        position -= right * offset;
    if (direction == RIGHT)
        position += right * offset;
}

void EularCamera::processMouseInput(float offsetX, float offsetY, bool constraint) {
    offsetX *= mouseSensitivity;
    offsetY *= mouseSensitivity;

    yaw   += offsetX;
    pitch += offsetY;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constraint) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}
