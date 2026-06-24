#pragma once

#include <deque>
#include <string>

class WorkingMemory
{
public:

    void Add(
        const std::string& text
    );

    std::string BuildContext() const;

private:

    std::deque<std::string>
        recentMessages;

    static constexpr
        size_t MAX_MESSAGES = 10;
};