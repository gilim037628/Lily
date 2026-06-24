#pragma once

#include "MemoryEntry.h"

#include <vector>
#include <string>

class MemoryManager
{
public:

    //---------------------------------
    // Long Memory
    //---------------------------------

    void AddMemory(
        const MemoryEntry& entry
    );

    void RemoveMemory(
        const std::string& id
    );

    //---------------------------------
    // Short Memory
    //---------------------------------

    void AddShortMemory(
        const MemoryEntry& entry
    );

    void ClearShortMemory();

    //---------------------------------
    // Prompt Builder
    //---------------------------------

    std::string BuildPrompt(
        const std::string& userPrompt
    ) const;

    //---------------------------------
    // Access
    //---------------------------------

    const std::vector<MemoryEntry>&
    GetLongMemory() const;

    const std::vector<MemoryEntry>&
    GetShortMemory() const;

private:

    std::vector<MemoryEntry>
        shortMemory;

    std::vector<MemoryEntry>
        longMemory;
};