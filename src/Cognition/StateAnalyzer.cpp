#include "StateAnalyzer.h"

void StateAnalyzer::Process(
    const std::string& text,
    LilyState& state
)
{
    if(
        text.find("힘들")
        != std::string::npos
    )
    {
        state.empathy += 0.1f;
    }

    if(
        text.find("?")
        != std::string::npos
    )
    {
        state.curiosity += 0.05f;
    }

    if(
        text.find("마인크래프트")
        != std::string::npos
    )
    {
        state.topic =
            "Minecraft";
    }
}