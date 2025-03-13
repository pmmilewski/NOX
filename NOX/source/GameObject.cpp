#include "GameObject.h"

#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include "WwiseIntegration.h"

using SoundEngine = WwiseIntegration;


GameObject::GameObject(glm::vec3 position, float rotationAngleDeg, glm::vec3 rotationAxis, glm::vec3 scale, GameObjectGeoPrimitive primitive, GameObjectMobility mobility)
{
    this->position = position;
    transform = glm::translate(transform, position);
    if (rotationAngleDeg != 0.0f)
    {
        transform = glm::rotate(transform, glm::radians(rotationAngleDeg), rotationAxis);
    }
    transform = glm::scale(transform, scale);
    this->primitive = primitive;
    this->mobility = mobility;
}

GameObject::~GameObject()
{
    //AK::SoundEngine::UnregisterGameObj(soundObject);
}

void GameObject::PostSoundEvent(std::string name)
{
    SoundEngine::PostEvent(soundObject, name);
}

void GameObject::CreateSoundObject()
{
    soundObject = SoundEngine::GetGameObjectId();
    AK::SoundEngine::RegisterGameObj(soundObject);
    AkSoundPosition EmitterPosition;
    EmitterPosition.SetPosition(position.x, position.y, position.z);
    EmitterPosition.SetOrientation(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    AK::SoundEngine::SetPosition(soundObject, EmitterPosition);
}
