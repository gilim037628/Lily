#pragma once

#include <string>

#include "../Memory/MemoryManager.h"
#include "../Memory/MemoryAnalyzer.h"
#include "../LLM/QwenProvider.h"
#include "../Cognition/LilyState.h"
#include "../Cognition/WorkingMemory.h"
#include "../Cognition/StateAnalyzer.h"

class RuntimeManager
{
public:

    bool Initialize();

    bool LoadModel(
        const std::string& modelPath
    );

    bool IsLoaded() const;

    std::string Generate(
        const std::string& prompt
    );

    MemoryManager&
    GetMemoryManager();

private:

    std::string BuildMemoryContext();

private:

    bool modelLoaded = false;

    MemoryManager memoryManager;
    MemoryAnalyzer memoryAnalyzer;

    QwenProvider qwen;

    LilyState state;

    WorkingMemory workingMemory;

    StateAnalyzer stateAnalyzer;
};