#include "EularCamera.h"
 
EularCamera::EularCamera(glm::vec3 mPosition, glm::vec3 mUp, float mYaw, float mPitch):front(glm::vec3(0.0f, 0.0f, -1.0f)), 
                movementSpeed(SPEED),
                mouseSensitivity(SENSITIVITY), zoom(ZOOM){
        position = mPosition;
        worldUp = mUp;
        yaw = mYaw;
        pitch = mPitch;
        updateCameraVectors();
}

glm::mat4 EularCamera::getPerspectiveMat() {
        return glm::perspective(glm::radians(zoom),
                                (float) Context::Instance().width / (float) Context::Instance().height, 0.1f, 100.0f);
}

glm::mat4 EularCamera::getViewMat() {
        return glm::lookAt(position, position + front, up);
    };

glm::vec3 EularCamera::getEyePosition() {
    return this->position;
}

void EularCamera::processMouseInput(float offsetX, float offsetY, bool constraint) {
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

void EularCamera::processKeyInput(CameraMove move, float deltaTime) {
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

void EularCamera::processMouseScroll(float offset) {
        // TODO: a better zoom handling
        if (zoom >= 1.0f && zoom <= 45.0f)
            zoom -= offset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 45.0f)
            zoom = 45.0f;
    }

void EularCamera::updateCameraVectors() {
        glm::vec3 tFront;
        tFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        tFront.y = sin(glm::radians(pitch));
        tFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(tFront);

        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    };