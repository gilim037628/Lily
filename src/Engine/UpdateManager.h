#pragma once

class VisionManager;
class MainWindow;

class UpdateManager
{
public:

    void Initialize(
        VisionManager* vision,
        MainWindow* window
    );

    void Update();

private:

    VisionManager* vision = nullptr;
    MainWindow* mainWindow = nullptr;
};