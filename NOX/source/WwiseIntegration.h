#pragma once
#include <atomic>
#include <string>


class WwiseIntegration
{
private:
    static uint64_t GameObjectId;
    
public:
    static bool InitWwise();
    static void InitWwiseComm();
    static void TermWwise();
    static void TermWwiseComm();
    static void PostEvent(uint64_t gameObject, std::string event);
    static void SetState(std::string stateGroup, std::string state);
    static void SetParameter(uint64_t gameObject, std::string parameter, float value);
    static void RenderAudio();
    static uint64_t GetGameObjectId() { return GameObjectId++; }
};
