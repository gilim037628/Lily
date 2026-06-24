#include "MemoryAnalyzer.h"

#include <ctime>

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