#include "RuntimeManager.h"

bool RuntimeManager::Initialize()
{
    return true;
}

bool RuntimeManager::IsLoaded() const
{
    return modelLoaded;
}

bool RuntimeManager::LoadModel(
    const std::string& modelPath
)
{
    modelLoaded =
        qwen.Initialize(
            modelPath
        );

    return modelLoaded;
}

std::string RuntimeManager::Generate(
    const std::string& prompt
)
{

    workingMemory.Add(
        prompt
    );

    stateAnalyzer.Process(
        prompt,
        state
    );
    //---------------------------------
    // Memory Save
    //---------------------------------

    if(
        memoryAnalyzer.ShouldSave(
            prompt
        )
    )
    {
        memoryManager.AddMemory(
            memoryAnalyzer.CreateMemory(
                prompt
            )
        );
    }

    //---------------------------------
    // Memory Context
    //---------------------------------

    std::string finalPrompt =
        BuildMemoryContext();

    finalPrompt +=
        "\nUser: ";

    finalPrompt +=
        prompt;

    //---------------------------------
    // TODO:
    // 실제 Qwen 호출
    //---------------------------------

    if(modelLoaded)
    {
        std::string response =
            qwen.Generate(
                finalPrompt
            );

        workingMemory.Add(
            response
        );

        return response;
    }

    return
        "[MODEL NOT LOADED]";
}

MemoryManager&
RuntimeManager::GetMemoryManager()
{
    return memoryManager;
}

std::string RuntimeManager::BuildMemoryContext()
{
    std::string context;

    //---------------------------------
    // State
    //---------------------------------

    context +=
        "Current State\n";

    context +=
        "Empathy: "
        + std::to_string(
            state.empathy
        )
        + "\n";

    context +=
        "Curiosity: "
        + std::to_string(
            state.curiosity
        )
        + "\n";

    context +=
        "Topic: "
        + state.topic
        + "\n\n";

    //---------------------------------
    // Long Memory
    //---------------------------------

    context +=
        "Long Term Memory:\n";

    const auto& memories =
        memoryManager.GetLongMemory();

    for(
        const auto& memory
        : memories
    )
    {
        context += "- ";

        context +=
            memory.content;

        context += "\n";
    }

    context += "\n";

    //---------------------------------
    // Working Memory
    //---------------------------------

    context +=
        "Recent Conversation:\n";

    context +=
        workingMemory.BuildContext();

    context +=
        "\n";

    return context;
}