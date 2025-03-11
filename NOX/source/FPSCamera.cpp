#include "FPSCamera.h"

void FPSCamera::MoveCamera(glm::vec3 directionsFRU, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    glm::vec3 movementVector = Front * directionsFRU.x * velocity + Right * directionsFRU.y * velocity + Up * directionsFRU.z * velocity;
    for (int i = 0; i < 3; ++i)
    {
        if (WorldUp[i] != 0.0f)
        {
            movementVector[i] = 0.0f;
        }
    }
    Position += movementVector;
    UpdateCameraState();
}