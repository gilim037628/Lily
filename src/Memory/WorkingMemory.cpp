#include "WorkingMemory.h"

void WorkingMemory::Add(
    const std::string& text
)
{
    history.push_back(text);

    if(history.size() > 10)
    {
        history.erase(history.begin());
    }
}

std::string WorkingMemory::BuildContext() const
{
    std::string context;

    for(const auto& line : history)
    {
        context += line;
        context += "\n";
    }

    return context;
}