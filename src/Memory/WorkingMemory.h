#pragma once

#include <string>
#include <vector>

class WorkingMemory
{
public:

    void Add(
        const std::string& text
    );

    std::string BuildContext() const;

private:

    std::vector<std::string> history;
};