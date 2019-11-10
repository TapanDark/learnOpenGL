#ifndef LOGL_CAMERA_UTIL
#define LOGL_CAMERA_UTIL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
private:
    glm::vec3 position;
    glm::vec3 viewDirection;
    glm::vec2 oldMousePosition;
    glm::vec3 sideAxis;
    const float ROTATION_SPEED;
    const float MOVEMENT_SPEED;
    const glm::vec3 UP;

public:
    Camera();
    glm::mat4 getViewTransformMatrix();
    void mouseUpdate(const glm::vec2 newMousePosition);
    void moveForward();
    void moveBackward();
    void strafeLeft();
    void strafeRight();
};

#endif