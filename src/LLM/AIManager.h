#pragma once

#include <memory>
#include <string>

#include "ILLMProvider.h"

class RuntimeManager;

class AIManager
{
public:

    AIManager(
        RuntimeManager& runtime
    );

    std::string Generate(
        const std::string& prompt
    );

private:

    RuntimeManager& runtime;

    std::unique_ptr<ILLMProvider>
        provider;
};