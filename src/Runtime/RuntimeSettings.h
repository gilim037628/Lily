#pragma once

#include <string>

struct RuntimeSettings
{
    std::string modelPath;

    int contextSize = 4096;

    int threads = 8;

    bool useGPU = false;
};