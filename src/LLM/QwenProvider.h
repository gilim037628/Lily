#pragma once

#include <string>

class QwenProvider
{
public:

    bool Initialize(
        const std::string& modelDir
    );

    bool IsInitialized() const;

    std::string Generate(
        const std::string& prompt
    );

private:

    bool initialized = false;

    std::string loadedModelPath;
};