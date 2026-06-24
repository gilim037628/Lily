#pragma once

#include <string>
#include <vector>

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