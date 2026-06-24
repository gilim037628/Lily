#pragma once

#include "../Memory/MemoryManager.h"

class SettingsSidebar
{
public:

    void Render(
        MemoryManager& memory
    );

private:

    int selectedTab = 0;
};