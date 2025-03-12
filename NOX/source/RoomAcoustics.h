#pragma once
#include <vector>
#include "GameObject.h"

class RoomAcoustics
{
private:
    std::vector<GameObject> SceneObjects;

public:
    RoomAcoustics() = default;
    void PopulateScene();
    std::vector<GameObject>& GetSceneObjects() { return SceneObjects; };
};
