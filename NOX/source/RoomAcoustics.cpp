#include "RoomAcoustics.h"
#include "WwiseIntegration.h"

using SoundEngine = WwiseIntegration;

void RoomAcoustics::PopulateScene()
{
    auto Floor = GameObject(glm::vec3(-5.0f, 0.0f, 5.0f),
        -90.0, glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(10.0f),
        GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    Floor.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    Floor.SetTexCoordScale({10.0f, 10.0f});

    auto Ceiling = GameObject(glm::vec3(-5.0f, 3.0f, -5.0f),
        90.0, glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(10.0f),
        GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    Ceiling.SetColor(glm::vec3(0.5f, 0.5f, 0.5f));
    Ceiling.SetTexCoordScale({10.0f, 10.0f});

    auto WallFront = GameObject(glm::vec3(-5.0f, 0.0f, -5.0f),
    0  , glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallFront.SetColor(glm::vec3(0.0f, 0.414f, 0.305f));
    WallFront.SetTexCoordScale({10.0f, 3.0f});

    auto WallBack = GameObject(glm::vec3(-5.0f, 3.0f, 5.0f),
    180  , glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallBack.SetColor(glm::vec3(0.0f, 0.414f, 0.305f));
    WallBack.SetTexCoordScale({10.0f, 3.0f});

    auto WallLeft = GameObject(glm::vec3(-5.0f, 0.0f, 5.0f),
    90  , glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallLeft.SetColor(glm::vec3(0.0f, 0.414f, 0.305f));
    WallLeft.SetTexCoordScale({10.0f, 3.0f});

    auto WallRight = GameObject(glm::vec3(5.0f, 0.0f, -5.0f),
    -90  , glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallRight.SetColor(glm::vec3(0.0f, 0.414f, 0.305f));
    WallRight.SetTexCoordScale({10.0f, 3.0f});

    auto SoundSource = GameObject(glm::vec3(0.0f, 1.5f, 0.0f),
        0, glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.2f, 0.2f, 0.2f),
        GameObjectGeoPrimitive::Cube, GameObjectMobility::Static);
    SoundSource.SetColor({1.0f, 0.84f, 0.0f});
    SoundSource.SetTexCoordScale({0.0f, 0.0f});
    SoundSource.SetOriented(true);
    SoundSource.CreateSoundObject();
    SoundEngine::SetState("TestSignal", "Pink");
    SoundSource.PostSoundEvent("Play_TestSignal");
    
    SceneObjects.emplace_back(Floor);
    SceneObjects.emplace_back(Ceiling);
    SceneObjects.emplace_back(WallFront);
    SceneObjects.emplace_back(WallBack);
    SceneObjects.emplace_back(WallLeft);
    SceneObjects.emplace_back(WallRight);
    SceneObjects.emplace_back(SoundSource);
}
