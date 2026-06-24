#pragma once

#include "LilyState.h"

#include <string>

class StateAnalyzer
{
public:

    void Process(
        const std::string& text,
        LilyState& state
    );
};