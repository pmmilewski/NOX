#include "WwiseIntegration.h"

#include  <iostream>
#include <thread>

#include <AK/SoundEngine/Common/AkMemoryMgrModule.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/Comm/AkCommunication.h>
#include <AK/Plugin/AkToneSourceFactory.h>

#include "AkDefaultIOHookDeferred.h"

CAkDefaultIOHookDeferred g_blockingDevice;
uint64_t WwiseIntegration::GameObjectId = 0;

namespace AK
{
    void* AllocHook(size_t size) { return malloc(size); }
    void FreeHook(void* ptr) { free(ptr); }
}

bool WwiseIntegration::InitWwise()
{
    AkMemSettings memSettings;
    AK::MemoryMgr::GetDefaultSettings(memSettings);
    AK::MemoryMgr::Init(&memSettings);

    AkStreamMgrSettings stmSettings;
    AK::StreamMgr::GetDefaultSettings(stmSettings);
    AK::StreamMgr::Create(stmSettings);

    AkDeviceSettings deviceSettings;
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);
    g_blockingDevice.Init(deviceSettings);
    g_blockingDevice.SetBasePath(AKTEXT("wwise/GeneratedSoundBanks"));

    AkInitSettings initSettings;
    AkPlatformInitSettings platformInitSettings;
    AK::SoundEngine::GetDefaultInitSettings(initSettings);
    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
    AK::SoundEngine::Init(&initSettings, &platformInitSettings);

    AkBankID bankID;
    AK::SoundEngine::LoadBank(AKTEXT("Init.bnk"), bankID);
    AK::SoundEngine::LoadBank(AKTEXT("SFX.bnk"), bankID);

    return true;
}

void WwiseIntegration::InitWwiseComm()
{
    AkCommSettings commSettings;
    AK::Comm::GetDefaultInitSettings(commSettings);
    AK::Comm::Init(commSettings);
}

void WwiseIntegration::TermWwise()
{
    AK::SoundEngine::UnloadBank(AKTEXT("Init.bnk"), nullptr);
    AK::SoundEngine::UnloadBank(AKTEXT("SFX.bnk"), nullptr);

    AK::SoundEngine::Term();
    g_blockingDevice.Term();

    if (AK::IAkStreamMgr::Get())
    {
        AK::IAkStreamMgr::Get()->Destroy();
    }

    AK::MemoryMgr::Term();
}

void WwiseIntegration::TermWwiseComm()
{
    AK::Comm::Term();
}

void WwiseIntegration::PostEvent(uint64_t gameObject, std::string event)
{
    AK::SoundEngine::PostEvent(event.data(), gameObject);
}

void WwiseIntegration::SetState(std::string stateGroup, std::string state)
{
    AK::SoundEngine::SetState(stateGroup.data(), state.data());
}

void WwiseIntegration::SetParameter(uint64_t gameObject, std::string parameter, float value)
{
    AK::SoundEngine::SetRTPCValue(parameter.data(), value, gameObject);
}

void WwiseIntegration::RenderAudio()
{
    AK::SoundEngine::RenderAudio();
}
