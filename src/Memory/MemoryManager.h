#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "MemoryCategory.h"

struct MemoryEntry
{
    std::string id;

    MemoryCategory category =
        MemoryCategory::General;

    std::string content;

    float importance = 1.0f;

    uint64_t timestamp = 0;
};

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

const char* ToString(
    MemoryCategory category
);

class MemoryAnalyzer
{
public:

    bool ShouldSave(
        const std::string& text
    ) const;

    MemoryEntry CreateMemory(
        const std::string& text
    ) const;

private:

    std::string GenerateId() const;
};