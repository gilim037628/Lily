#pragma once

#include <string>

class PromptManager
{
public:

    std::string BuildPrompt(
        const std::string& characterPrompt,
        const std::string& memory,
        const std::string& userInput
    );
};