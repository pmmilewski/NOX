#include "RoomAcoustics.h"

void RoomAcoustics::PopulateScene()
{
    auto Floor = GameObject(glm::vec3(-5.0f, 0.0f, 5.0f),
        -90.0, glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(10.0f),
        GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    Floor.SetColor(glm::vec3(0.5f, 0.5f, 0.5f));
    Floor.SetTexCoordScale({10.0f, 10.0f});

    auto Ceiling = GameObject(glm::vec3(-5.0f, 3.0f, -5.0f),
        90.0, glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(10.0f),
        GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    Ceiling.SetColor(glm::vec3(0.25f, 0.25f, 0.25f));
    Ceiling.SetTexCoordScale({10.0f, 10.0f});

    auto WallFront = GameObject(glm::vec3(-5.0f, 0.0f, -5.0f),
    0  , glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallFront.SetColor(glm::vec3(0.7f, 0.0f, 0.0f));
    WallFront.SetTexCoordScale({10.0f, 3.0f});

    auto WallBack = GameObject(glm::vec3(-5.0f, 3.0f, 5.0f),
    180  , glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallBack.SetColor(glm::vec3(0.0f, 0.7f, 0.0f));
    WallBack.SetTexCoordScale({10.0f, 3.0f});

    auto WallLeft = GameObject(glm::vec3(-5.0f, 0.0f, 5.0f),
    90  , glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallLeft.SetColor(glm::vec3(0.0f, 0.0f, 0.7f));
    WallLeft.SetTexCoordScale({10.0f, 3.0f});

    auto WallRight = GameObject(glm::vec3(5.0f, 0.0f, -5.0f),
    -90  , glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(10.0f, 3.0f, 1.0f),
    GameObjectGeoPrimitive::Plane, GameObjectMobility::Static);
    WallRight.SetColor(glm::vec3(0.7f, 0.7f, 0.0f));
    WallRight.SetTexCoordScale({10.0f, 3.0f});
    

    SceneObjects.emplace_back(Floor);
    SceneObjects.emplace_back(Ceiling);
    SceneObjects.emplace_back(WallFront);
    SceneObjects.emplace_back(WallBack);
    SceneObjects.emplace_back(WallLeft);
    SceneObjects.emplace_back(WallRight);
}
