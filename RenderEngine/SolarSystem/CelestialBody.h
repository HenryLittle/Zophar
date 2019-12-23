//
// Created by Henry Little on 2019/10/14.
//

#ifndef RENDERENGINE_PLANET_H
#define RENDERENGINE_PLANET_H

#include "./Orbit/Orbit.hpp"
#include "../ObjectModel/Model.hpp"


#include <vector>
#include <string>
#include <cmath>


class CelestialBody {
public:
    CelestialBody *centerBody = nullptr;
    Orbit *orbit;

    string name;

    float bodyRadius;
    float rotationAngle; // angle respect to the orbit plane
    float orbitRadius;
    float orbitAngle;
    float rotationAngleSpeed = 1.0f;
    float revolutionAngleSpeed = 1.0f;

    Model *objectModel;

    glm::mat4 objectModelMat; // the basic model matrix
    glm::mat4 rotationMat;
    glm::mat4 revolutionMat;
    glm::vec3 rotationAxis;
    glm::vec3 revolutionAxis;
    glm::vec3 revolutionAxisInv;
    // configurable
    static float timeScaleFactor; // speed up/down the celestial objects
    static bool showOrbit; // whether to render orbit
    static bool pause;
    // cache
    double prevTime;

    CelestialBody(string name, float bodyRadius = 1.0f, 
                  float orbitRadius = 0.0f, float orbitAngle = 0.0f,
                  float rotationAngle = 0.0f, float rotationAngleSpeed = 1.0f, 
                  float revolutionAngleSpeed = 1.0f);

    void setCenterBody(CelestialBody *body);
    
    // return the composed revolution matrix
    glm::mat4 getRevolutionMatrix(double time);

    void render(Shader shader);

private:
    void initAxis();

    glm::mat4 calculateObjectModelMat();

    glm::mat4 calculateRotationMat(double time);

    glm::mat4 calculateRevolutionMat(double time);

    glm::mat4 getOrbitModelMatrix(double time);

};



#endif //RENDERENGINE_PLANET_H