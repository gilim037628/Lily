#include "UpdateManager.h"

#include "../Vision/VisionManager.h"
#include "../UI/MainWindow.h"

void UpdateManager::Initialize(
    VisionManager* visionManager,
    MainWindow* window
)
{
    vision = visionManager;
    mainWindow = window;
}

void UpdateManager::Update()
{
    //----------------------------------
    // Vision
    //----------------------------------

    if (vision)
    {
        vision->Update();
    }

    //----------------------------------
    // UI
    //----------------------------------

    if (mainWindow)
    {
        mainWindow->SetVisionManager(vision);
        mainWindow->Render();
    }

    //----------------------------------
    // 앞으로 추가될 것
    //----------------------------------

    // Memory
    // Audio
    // Input
    // Live2D
    // Planner
}