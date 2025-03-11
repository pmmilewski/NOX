#pragma once
#include "Camera.h"

class FPSCamera : public Camera
{
public:

    using Camera::Camera;
    void MoveCamera(glm::vec3 directionsFRU, float deltaTime) override;
};