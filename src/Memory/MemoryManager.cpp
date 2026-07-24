#include "MemoryManager.h"
#include "MemoryCategory.h"

#include <ctime>
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

bool MemoryAnalyzer::ShouldSave(
    const std::string& text
) const
{
    //---------------------------------
    // 이름
    //---------------------------------

    if(
        text.find("name") !=
        std::string::npos
    )
    {
        return true;
    }

    //---------------------------------
    // 좋아하는 것
    //---------------------------------

    if(
        text.find("like") !=
        std::string::npos
    )
    {
        return true;
    }

    //---------------------------------
    // 목표
    //---------------------------------

    if(
        text.find("goal") !=
        std::string::npos
    )
    {
        return true;
    }

    //---------------------------------
    // 프로젝트
    //---------------------------------

    if(
        text.find("project") !=
        std::string::npos
    )
    {
        return true;
    }

    return false;
}

MemoryEntry MemoryAnalyzer::CreateMemory(
    const std::string& text
) const
{
    MemoryEntry entry;

    entry.id =
        GenerateId();

    entry.content =
        text;

    entry.importance =
        1.0f;

    entry.timestamp =
        static_cast<uint64_t>(
            std::time(nullptr)
        );

    //---------------------------------
    // Identity
    //---------------------------------

    if(
        text.find("name")
        != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Identity;
    }

    //---------------------------------
    // Preference
    //---------------------------------

    else if(
        text.find("like")
        != std::string::npos ||

        text.find("dislike")
        != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Preference;
    }

    //---------------------------------
    // Goal
    //---------------------------------

    else if(
        text.find("goal")
        != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Goal;
    }

    //---------------------------------
    // Project
    //---------------------------------

    else if(
        text.find("project")
        != std::string::npos ||

        text.find("develop")
        != std::string::npos ||

        text.find("making")
        != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Project;
    }

    //---------------------------------
    // Interest
    //---------------------------------

    else if(
        text.find("interest") != std::string::npos ||
        text.find("study") != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Interest;
    }

    //---------------------------------
    // Habit
    //---------------------------------

    else if(
        text.find("habit") != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Habit;
    }

    //---------------------------------
    // Game
    //---------------------------------

    else if(
        text.find("MineCraft") != std::string::npos ||
        text.find("game") != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Game;
    }

    //---------------------------------
    // Account
    //---------------------------------

    else if(
        text.find("account") != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::Account;
    }

    //---------------------------------
    // System
    //---------------------------------

    else if(
        text.find("Fabric") != std::string::npos ||
        text.find("NeoForge") != std::string::npos ||
        text.find("Qwen") != std::string::npos
    )
    {
        entry.category =
            MemoryCategory::System;
    }

    //---------------------------------
    // Personal
    //---------------------------------

    else
    {
        entry.category =
            MemoryCategory::Personal;
    }

    return entry;
}

std::string MemoryAnalyzer::GenerateId() const
{
    return
        "mem_" +
        std::to_string(
            std::time(nullptr)
        );
}