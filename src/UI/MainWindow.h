#pragma once

#include "Panels.h"
#include "../Runtime/RuntimeManager.h"
#include "../Memory/MemoryManager.h"
#include "../Vision/VisionManager.h"

class MainWindow
{
public:

    MainWindow();

    void SetVisionManager(
        VisionManager* manager
    );

    void Render();

    RuntimeManager&
    GetRuntime();

    bool Initialize();
    void Update();

    GridBuilder& GetGridBuilder();

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

    VisionManager* vision = nullptr;

    GridRenderer gridRenderer;

    GridBuilder girdBuilder;
};