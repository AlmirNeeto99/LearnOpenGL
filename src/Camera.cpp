#include "headers/Camera.hpp"

Camera::Camera() {}

Camera::Camera(vec3 position, vec3 direction)
{
    this->position = position;
    this->direction = direction;
}

double Camera::getPitch()
{
    return this->pitch;
}
double Camera::getYaw()
{
    return this->yaw;
}
double Camera::getRoll()
{
    return this->roll;
}
vec3 Camera::getDirection()
{
    return this->direction;
}
vec3 Camera::getUp()
{
    return this->up;
}
vec3 Camera::getPosition()
{
    return this->position;
}
void Camera::setDirection(vec3 direction)
{
    this->direction = direction;
}
void Camera::setUp(vec3 up)
{
    this->up = up;
}
void Camera::setPosition(vec3 position)
{
    this->position = position;
}
void Camera::setPitch(double pitch)
{
    this->pitch = pitch;
}
void Camera::setRoll(double roll)
{
    this->roll = roll;
}
void Camera::setYaw(double yaw)
{
    this->yaw = yaw;
}
mat4x4 Camera::update(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->position += this->direction * this->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->position -= this->direction * this->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->position -= normalize(cross(this->direction, this->up)) * this->speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->position += normalize(cross(this->direction, this->up)) * this->speed;
    }
    glfwGetCursorPos(window, &this->xPos, &this->yPos);
    double offsetX = this->xPos - this->lastX;
    double offsetY = this->lastY - this->yPos;
    this->lastX = this->xPos;
    this->lastY = this->yPos;
    this->pitch += offsetY * this->speed * .5;
    this->yaw += offsetX * this->speed * .5;

    this->direction.x = cos(radians(this->yaw));
    this->direction.y = sin(radians(this->pitch));
    this->direction.z = cos(radians(this->pitch)) * sin(radians(this->yaw));

    return lookAt(
        this->position,
        this->position + this->direction,
        this->up);
}