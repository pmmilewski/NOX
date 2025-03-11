#pragma once
#include <glm/glm.hpp>

constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float ZOOM = 45.0f;

constexpr float MOVEMENT_SPEED = 10.0f;
constexpr float ROTATION_SPEED = 10.0f;
constexpr float ZOOM_SPEED = 100.0f;

class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH);

    Camera(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f,
        float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f,
        float yaw = YAW, float pitch = PITCH);

    virtual ~Camera() = default;
    
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::mat4 View;

    float Yaw;
    float Pitch;
    float Zoom;

    float MovementSpeed;
    float RotationSpeed;
    float ZoomSpeed;
    
    glm::mat4 GetCameraMatrix() const;
    float GetZoom() const;
    virtual void MoveCamera(glm::vec3 directionsFRU, float deltaTime);
    void RotateCamera(float xOffset, float yOffset, float deltaTime, bool constrainPitch = true);
    void ZoomCamera(float yOffset, float deltaTime);

    void SetMovementSpeed(float newValue);
    void SetRotationSpeed(float newValue);
    void SetZoomSpeed(float newValue);

protected:
    void UpdateCameraState();
};