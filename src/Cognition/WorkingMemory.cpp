#include "WorkingMemory.h"

void WorkingMemory::Add(
    const std::string& text
)
{
    recentMessages.push_back(
        text
    );

    while(
        recentMessages.size()
        > MAX_MESSAGES
    )
    {
        recentMessages.pop_front();
    }
}

std::string
WorkingMemory::BuildContext() const
{
    std::string result;

    for(
        const auto& msg
        : recentMessages
    )
    {
        result += msg;
        result += "\n";
    }

    return result;
}