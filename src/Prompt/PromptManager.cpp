#include "PromptManager.h"

std::string PromptManager::BuildPrompt(
    const std::string& systemPrompt,
    const std::string& memoryContext,
    const std::string& userInput
)
{
    return

        systemPrompt +

        "\n\n=== Memory ===\n" +

        memoryContext +

        "\n\n=== User ===\n" +

        userInput;
}