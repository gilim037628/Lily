#include "AIManager.h"

#include "LocalProvider.h"

AIManager::AIManager(
    RuntimeManager& runtime
)
    : runtime(runtime)
{
    provider =
        std::make_unique<
            LocalProvider
        >();
}

std::string AIManager::Generate(
    const std::string& userMessage
)
{
    return provider->Generate(
        userMessage
    );
}