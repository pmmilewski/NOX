#include "WwiseIntegration.h"

#include  <iostream>
#include <thread>

#include <AK/SoundEngine/Common/AkMemoryMgrModule.h>
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <AK/Comm/AkCommunication.h>

#include "AkDefaultIOHookDeferred.h"

CAkDefaultIOHookDeferred g_blockingDevice;

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

void WwiseIntegration::PlayEvent()
{
    AkGameObjectID gameObjectID = 1;
    AK::SoundEngine::RegisterGameObj(gameObjectID, "GameObject1");
    AK::SoundEngine::PostEvent(AKTEXT("Play_SFX_1"), gameObjectID);
    AK::SoundEngine::UnregisterGameObj(gameObjectID);
}

void WwiseIntegration::RenderAudio()
{
    AK::SoundEngine::RenderAudio();
}
