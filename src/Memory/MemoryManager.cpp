#include "MemoryManager.h"

#include <algorithm>

void MemoryManager::AddMemory(
    const MemoryEntry& entry
)
{
    longMemory.push_back(
        entry
    );
}

void MemoryManager::RemoveMemory(
    const std::string& id
)
{
    longMemory.erase(
        std::remove_if(
            longMemory.begin(),
            longMemory.end(),

            [&](const MemoryEntry& memory)
            {
                return memory.id == id;
            }
        ),

        longMemory.end()
    );
}

void MemoryManager::AddShortMemory(
    const MemoryEntry& entry
)
{
    shortMemory.push_back(
        entry
    );

    constexpr size_t MAX_SHORT_MEMORY = 20;

    if(
        shortMemory.size()
        > MAX_SHORT_MEMORY
    )
    {
        shortMemory.erase(
            shortMemory.begin()
        );
    }
}

void MemoryManager::ClearShortMemory()
{
    shortMemory.clear();
}

std::string MemoryManager::BuildPrompt(
    const std::string& userPrompt
) const
{
    std::string prompt;

    //---------------------------------
    // Long Memory
    //---------------------------------

    prompt +=
        "[LONG MEMORY]\n";

    for(
        const auto& memory
        : longMemory
    )
    {
        prompt += "- ";
        prompt += memory.content;
        prompt += "\n";
    }

    //---------------------------------
    // Short Memory
    //---------------------------------

    prompt +=
        "\n[RECENT CONVERSATION]\n";

    for(
        const auto& memory
        : shortMemory
    )
    {
        prompt += "- ";
        prompt += memory.content;
        prompt += "\n";
    }

    //---------------------------------
    // User
    //---------------------------------

    prompt +=
        "\n[USER]\n";

    prompt +=
        userPrompt;

    return prompt;
}

const std::vector<MemoryEntry>&
MemoryManager::GetLongMemory() const
{
    return longMemory;
}

const std::vector<MemoryEntry>&
MemoryManager::GetShortMemory() const
{
    return shortMemory;
}