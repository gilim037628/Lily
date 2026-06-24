#include "CharacterManager.h"

void CharacterManager::LoadDefaults()
{
    Character lily;

    lily.name = "Lily";

    lily.promptFile =
        "characters/lily/prompt.txt";

    lily.memoryFile =
        "characters/lily/memory.json";

    lily.live2dModel =
        "characters/lily/model/model3.json";

    characters.push_back(lily);
}

const Character&
CharacterManager::GetCurrent() const
{
    return characters[0];
}