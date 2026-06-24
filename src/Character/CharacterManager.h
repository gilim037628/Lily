#pragma once

#include "Character.h"

#include <vector>

class CharacterManager
{
public:

    void LoadDefaults();

    const Character& GetCurrent() const;

private:

    std::vector<Character> characters;
};