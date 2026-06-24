#include "LilyCore.h"

LilyCore::LilyCore(
    EventBus& bus,
    ILLMProvider& llm
)
    :
    eventBus(bus),
    llmProvider(llm)
{
    eventBus.Subscribe<UserInputEvent>(
        [this](const UserInputEvent& event)
        {
            OnUserInput(event);
        }
    );
}

void LilyCore::OnUserInput(
    const UserInputEvent& event
)
{
    std::string response =
        llmProvider.Generate(event.text);

    eventBus.Publish(
        LLMResponseEvent
        {
            response
        }
    );
}