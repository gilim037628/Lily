#pragma once

#include "ILLMProvider.h"

class LocalProvider
    : public ILLMProvider
{
public:

    LocalProvider();

    std::string Generate(
        const std::string& prompt
    ) override;

};