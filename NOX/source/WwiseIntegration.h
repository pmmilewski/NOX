#pragma once
#include <atomic>

class WwiseIntegration
{
public:
    bool InitWwise();
    void InitWwiseComm();
    void TermWwise();
    void TermWwiseComm();
    void PlayEvent();
    void RenderAudio();
};
