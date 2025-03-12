#include "GameObject.h"

GameObject::GameObject(glm::vec3 position, float rotationAngleDeg, glm::vec3 rotationAxis, glm::vec3 scale, GameObjectGeoPrimitive primitive, GameObjectMobility mobility)
{
    transform = glm::translate(transform, position);
    if (rotationAngleDeg != 0.0f)
    {
        transform = glm::rotate(transform, glm::radians(rotationAngleDeg), rotationAxis);
    }
    transform = glm::scale(transform, scale);
    this->primitive = primitive;
    this->mobility = mobility;
}
