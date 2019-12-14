//
// Created by Henry Little on 2019/10/18.
//

#include "CelestialBody.hpp"

float CelestialBody::timeScaleFactor = 1.0f;
bool CelestialBody::pause = false;
bool CelestialBody::showOrbit = true;

CelestialBody::CelestialBody(string name, float bodyRadius, float orbitRadius, float orbitAngle, float rotationAngle, float rotationAngleSpeed, float revolutionAngleSpeed)
        : name(name), rotationAngle(rotationAngle), bodyRadius(bodyRadius), orbitRadius(orbitRadius),
          orbitAngle(orbitAngle), rotationAngleSpeed(rotationAngleSpeed), revolutionAngleSpeed(revolutionAngleSpeed) {
    // load the model
    objectModel = new Model("../res/" + name + "/" + name + ".obj");
    objectModelMat = calculateObjectModelMat();
    // initialize the orbit
    orbit = new Orbit();
    initAxis();
}

glm::mat4 CelestialBody::getRevolutionMatrix(double time) {
    glm::mat4 mat = centerBody == nullptr ? glm::mat4(1.0f) : centerBody->getRevolutionMatrix(time);
    revolutionMat = calculateRevolutionMat(time);
    return mat * revolutionMat;
}

void CelestialBody::render(Shader shader) {
    double time;
    if (pause) {
        time = prevTime;
    } else {
        time = glfwGetTime();
        prevTime = time;
    }
    // do the model matrix calculation
    rotationMat = calculateRotationMat(time);
    revolutionMat = getRevolutionMatrix(time);
    glm::mat4 model = revolutionMat * rotationMat * objectModelMat;
    // draw the planet
    shader.setMat4("model", model);
    objectModel->Draw(shader);
    if (showOrbit) {
        // render the orbit
        orbit->setModel(getOrbitModelMatrix(time));
        orbit->render();
    }
}

void CelestialBody::initAxis() {
    // rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    rotationAxis = glm::vec3(sin(rotationAngle), cos(rotationAngle), 0.0f);
    revolutionAxis = glm::vec3(sin(orbitAngle), cos(orbitAngle), 0.0f);
    revolutionAxisInv = glm::vec3(-sin(orbitAngle), -cos(orbitAngle), 0.0f);
}

glm::mat4 CelestialBody::calculateObjectModelMat() {
    // scale the model to the correct size using AU unit
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::rotate(mat, rotationAngle, glm::vec3(0.0f, 0.0f, -1.0f));
    mat = glm::scale(mat, glm::vec3(bodyRadius, bodyRadius, bodyRadius));
    return mat;
}

glm::mat4 CelestialBody::calculateRotationMat(double time) {
    // calculate the slef rotation matrices
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::rotate(mat, rotationAngleSpeed * (float) time * timeScaleFactor, rotationAxis);
    return mat;
}

glm::mat4 CelestialBody::calculateRevolutionMat(double time) {
    // calculate the revolution matrices
    glm::mat4 mat = glm::mat4(1.0f);
    // rotate the orbit plane
    mat = glm::rotate(mat, revolutionAngleSpeed * (float) time * timeScaleFactor, revolutionAxis);
    // translate from center
    mat = glm::translate(mat, glm::vec3(0.0f, 0.0f, orbitRadius));
    // *rotation axis compensation
    mat = glm::rotate(mat, revolutionAngleSpeed * (float) time * timeScaleFactor, -revolutionAxis);
    return mat;
}

glm::mat4 CelestialBody::getOrbitModelMatrix(double time) {
    // center rotate scale
    // center
    glm::mat4 mat = centerBody == nullptr ? glm::mat4(1.0f) : centerBody->getRevolutionMatrix(time);
    // rotate
    mat = glm::rotate(mat, orbitAngle, glm::vec3(0.0f, 0.0f, -1.0f));
    // scale
    mat = glm::scale(mat, glm::vec3(orbitRadius, orbitRadius, orbitRadius));
    return mat;
}