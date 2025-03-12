#pragma once
#include "commonVk.h"

enum class GameObjectGeoPrimitive
{
    None,
    Plane,
    Cube
};

enum class GameObjectMobility
{
    Static,
    Dynamic
};

class GameObject
{
private:
    glm::mat4 transform = {glm::mat4(1.0f)};
    GameObjectGeoPrimitive primitive = {GameObjectGeoPrimitive::None};
    GameObjectMobility mobility = {GameObjectMobility::Static};
    glm::vec3 color = glm::vec3(1.0f);

public:
    GameObject() = default;
    GameObject(glm::vec3 position, float rotationAngleDeg, glm::vec3 rotationAxis, glm::vec3 scale, GameObjectGeoPrimitive primitive, GameObjectMobility mobility);
    auto GetTransform() const { return transform; }
    auto GetPrimitive() const { return primitive; }
    auto GetMobility() const { return mobility; }
    void SetColor(glm::vec3 color) { this->color = color; }
    glm::vec3 GetColor() const { return color; }
};
