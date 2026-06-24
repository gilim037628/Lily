#pragma once

#include "EventBus.h"
#include "../LLM/ILLMProvider.h"
#include "Events.h"

class LilyCore
{
public:

    LilyCore(
        EventBus& bus,
        ILLMProvider& llm
    );

private:

    EventBus& eventBus;
    ILLMProvider& llmProvider;

    void OnUserInput(
        const UserInputEvent& event
    );
};