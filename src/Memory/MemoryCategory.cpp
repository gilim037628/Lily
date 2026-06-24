#include "MemoryCategory.h"

const char* ToString(
    MemoryCategory category
)
{
    switch(category)
    {
        case MemoryCategory::Identity:
            return "Identity";

        case MemoryCategory::Preference:
            return "Preference";

        case MemoryCategory::Goal:
            return "Goal";

        case MemoryCategory::Project:
            return "Project";

        case MemoryCategory::Interest:
            return "Interest";

        case MemoryCategory::Habit:
            return "Habit";

        case MemoryCategory::Game:
            return "Game";

        case MemoryCategory::Account:
            return "Account";

        case MemoryCategory::System:
            return "System";

        case MemoryCategory::Personal:
            return "Personal";

        default:
            return "General";
    }
}