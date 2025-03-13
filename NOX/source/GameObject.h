#pragma once
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkTypes.h>
#include "WwiseIntegration.h"
#include "commonVk.h"

using SoundEngine = WwiseIntegration;

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
    glm::vec3 position;
    GameObjectGeoPrimitive primitive = {GameObjectGeoPrimitive::None};
    GameObjectMobility mobility = {GameObjectMobility::Static};
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec2 texCoordScale = {1.0f, 1.0f};
    bool oriented = false;
    AkGameObjectID soundObject;

public:
    GameObject() = delete;
    GameObject(glm::vec3 position, float rotationAngleDeg, glm::vec3 rotationAxis, glm::vec3 scale, GameObjectGeoPrimitive primitive, GameObjectMobility mobility);
    ~GameObject();
    auto GetTransform() const { return transform; }
    auto GetPrimitive() const { return primitive; }
    auto GetMobility() const { return mobility; }
    void SetColor(glm::vec3 color) { this->color = color; }
    void SetTexCoordScale(glm::vec2 scale) { texCoordScale = scale; }
    auto GetTexCoordScale() const { return texCoordScale; }
    auto GetColor() const { return color; }
    void SetOriented(bool oriented) { this->oriented = oriented; }
    auto GetOriented() const { return oriented; }
    void CreateSoundObject();
    auto GetSoundObject() const { return soundObject; }
    void PostSoundEvent(std::string name);
};
