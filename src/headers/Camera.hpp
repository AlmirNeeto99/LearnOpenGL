#ifndef CAMERA_H

#include "glm/matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace glm;

#define CAMERA_H

class Camera
{
private:
    double pitch = 0, yaw = 0, roll = 0;
    vec3 up = vec3(0, 1, 0), direction = vec3(0, 0, -1), position = vec3(0, 0, 3);
    float speed = 10.0f;

public:
    Camera();
    Camera(vec3 position, vec3 direction);
    // \/ Angles \/
    double getPitch();
    double getYaw();
    double getRoll();
    void setPitch(double);
    void setYaw(double);
    void setRoll(double);
    // \/ Vectors \/
    vec3 getUp();
    vec3 getDirection();
    vec3 getPosition();
    void setUp(vec3);
    void setDirection(vec3);
    void setPosition(vec3);
    // \/ Speed \/
    float getSpeed();
    void setSpeed(float);
    /**
     * @return glm::mat4x4 The new updated view
    */
    mat4x4 update();
};

#endif