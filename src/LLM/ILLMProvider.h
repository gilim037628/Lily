#pragma once

#include <string>

class ILLMProvider
{
public:

    virtual ~ILLMProvider() = default;

    virtual std::string Generate(
        const std::string& prompt
    ) = 0;
};