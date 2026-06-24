#pragma once

enum class MemoryCategory
{
    Identity,
    Preference,
    Goal,
    Project,
    Interest,
    Habit,
    Game,
    Account,
    System,
    Personal,
    General
};

const char* ToString(
    MemoryCategory category
);