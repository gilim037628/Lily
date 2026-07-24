#pragma once

#include <string>
#include <vector>

#include "../Memory/MemoryManager.h"

enum class AIState
{
    Running,
    Background,
    Stopped
};

struct AIEntry
{
    std::string name;
    AIState state;
};

class AgentSidebar
{
public:

    AgentSidebar();

    void Render();

private:

    std::vector<AIEntry> agents;

    int selectedAI = -1;
};

class SettingsSidebar
{
public:

    void Render(
        MemoryManager& memory
    );

private:

    int selectedTab = 0;
};

class HeaderBar
{
public:

    void Render();
};

class StatusBar
{
public:

    void Render();
};

class RuntimeManager;

class ViewPanel
{
public:

    void Render(
        RuntimeManager& runtime
    );

private:

    char promptBuffer[1024] = "";

    std::string response;
};