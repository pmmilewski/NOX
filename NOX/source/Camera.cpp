#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"

void Camera::UpdateCameraState()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
    
    View = glm::lookAt(Position, Position + Front, Up);
}

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) :
    Front(glm::vec3(0, 0, -1)),
    Zoom(ZOOM),
    MovementSpeed(MOVEMENT_SPEED),
    RotationSpeed(ROTATION_SPEED),
    ZoomSpeed(ZOOM_SPEED)
{
    Position = pos;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraState();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
Front(glm::vec3(0, 0, -1)),
Zoom(ZOOM),
MovementSpeed(MOVEMENT_SPEED),
RotationSpeed(ROTATION_SPEED),
ZoomSpeed(ZOOM_SPEED)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    UpdateCameraState();
}

glm::mat4 Camera::GetCameraMatrix() const
{
    return View;
}

float Camera::GetZoom() const
{
    return Zoom;
}

void Camera::MoveCamera(glm::vec3 directionsFRU, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    
    Position += Front * directionsFRU.x * velocity + Right * directionsFRU.y * velocity + Up * directionsFRU.z * velocity;
    UpdateCameraState();
}

void Camera::RotateCamera(float xOffset, float yOffset, float deltaTime, bool constrainPitch)
{
    xOffset *= RotationSpeed * deltaTime;
    yOffset *= RotationSpeed * deltaTime;

    Yaw += xOffset;
    Pitch += yOffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    direction.y = sin(glm::radians(Pitch));
    direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(direction);
    UpdateCameraState();
}

void Camera::ZoomCamera(float yOffset, float deltaTime)
{
    Zoom -= (float)yOffset * ZoomSpeed * deltaTime;
    if (Zoom < 1.0f)
        Zoom = 1.0f;

    if(Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::SetMovementSpeed(float newValue)
{
    MovementSpeed = newValue;
}

void Camera::SetRotationSpeed(float newValue)
{
    RotationSpeed = newValue;
}

void Camera::SetZoomSpeed(float newValue)
{
    ZoomSpeed = newValue;
}