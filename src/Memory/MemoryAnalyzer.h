#pragma once

#include "../Memory/MemoryEntry.h"
#include "../Memory/MemoryCategory.h"

#include <string>

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