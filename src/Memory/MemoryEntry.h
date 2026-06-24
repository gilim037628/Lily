#pragma once

#include "MemoryCategory.h"

#include <string>
#include <cstdint>

struct MemoryEntry
{
    std::string id;

    MemoryCategory category =
        MemoryCategory::General;

    std::string content;

    float importance = 1.0f;

    uint64_t timestamp = 0;
};