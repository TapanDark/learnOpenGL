#include "camera.hpp"

Camera::Camera() : position(0.0f, 0.0f, 0.0f),
                   viewDirection(0.0f, 0.0f, -1.0f),
                   sideAxis(1.0f, 0.0f, 0.0f),
                   UP(0.0f, 1.0f, 0.0f), oldMousePosition(0.0f, 0.0f),
                   ROTATION_SPEED(0.1f), MOVEMENT_SPEED(0.1f) {}

void Camera::mouseUpdate(const glm::vec2 newMousePosition)
{
    glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
    viewDirection = (glm::mat3)glm::rotate(glm::radians(-mouseDelta.x) * ROTATION_SPEED, UP) * viewDirection;
    sideAxis = glm::cross(viewDirection, UP);
    viewDirection = (glm::mat3)glm::rotate(glm::radians(-mouseDelta.y) * ROTATION_SPEED, sideAxis) * viewDirection;
    oldMousePosition = newMousePosition;
}

glm::mat4 Camera::getViewTransformMatrix()
{
    return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::moveForward()
{
    position += viewDirection * MOVEMENT_SPEED;
}
void Camera::moveBackward()
{
    position -= viewDirection * MOVEMENT_SPEED;
}
void Camera::strafeLeft()
{
    position -= sideAxis * MOVEMENT_SPEED;
}
void Camera::strafeRight()
{
    position += sideAxis * MOVEMENT_SPEED;
}
