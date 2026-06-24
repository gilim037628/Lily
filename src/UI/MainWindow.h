#pragma once

#include "HeaderBar.h"
#include "ViewPanel.h"
#include "StatusBar.h"

#include "AgentSidebar.h"
#include "SettingsSidebar.h"
#include "../Runtime/RuntimeManager.h"
#include "../Memory/MemoryManager.h"

class MainWindow
{
public:

    MainWindow();

    void Render();

    RuntimeManager&
    GetRuntime();

private:

    HeaderBar headerBar;
    ViewPanel viewPanel;
    StatusBar statusBar;

    AgentSidebar agentSidebar;
    SettingsSidebar settingsSidebar;

    RuntimeManager runtime;
    MemoryManager memoryManager;

    bool showAgentPanel = false;
    bool showSettingsPanel = false;

    float leftWidth = 0.0f;
    float rightWidth = 0.0f;
};