#include "VisionManager.h"

#include <iostream>

bool VisionManager::Initialize()
{
    capture =
        std::make_unique<DesktopCapture>();

    return capture->Initialize();
}

void VisionManager::Update()
{
    std::cerr << "\n========== VISION UPDATE ==========\n";

    //----------------------------------
    // Capture
    //----------------------------------

    std::cout << "[1] Capture Start\n";

    if (!capture->Capture(frame))
    {
        std::cout << "[ERROR] Capture Failed\n";
        return;
    }

    std::cout
        << "[2] Capture Success ("
        << frame.width
        << " x "
        << frame.height
        << ")\n";

    //----------------------------------
    // Build Grid Pyramid
    //----------------------------------

    std::cout << "[3] Build Grid\n";

    gridBuilder.Build(frame);

    std::cout << "[4] Grid Built\n";

    //----------------------------------
    // Detect Changes
    //----------------------------------

    std::cout << "[5] ChangeDetector Start\n";

    changeDetector.Update(
        gridBuilder
    );

    std::cout << "[6] ChangeDetector End\n";

    //----------------------------------
    // Frame Counter
    //----------------------------------

    static int frameCounter = 0;

    frameCounter++;

    std::cout
        << "[7] Frame = "
        << frameCounter
        << "\n";

    //----------------------------------
    // Layers
    //----------------------------------

    const auto& layers =
        gridBuilder.GetLayers();

    std::cout
        << "[8] Layer Count = "
        << layers.size()
        << "\n";

    if (layers.size() < 4)
    {
        std::cout
            << "[ERROR] Layer Count < 4\n";
        return;
    }

    //----------------------------------
    // Layer
    //----------------------------------

    const auto& layer =
        layers[3];

    std::cout
        << "[9] Cell Count = "
        << layer.cells.size()
        << "\n";

    //----------------------------------
    // Debug
    //----------------------------------

    std::cout
        << "\n===== Vision Debug =====\n";

    size_t count =
        std::min<size_t>(
            5,
            layer.cells.size()
        );

    for(size_t i = 0; i < count; i++)
    {
        const auto& cell =
            layer.cells[i];

        std::cout
            << "Cell "
            << i
            << " RGB("
            << (int)cell.averageR
            << ", "
            << (int)cell.averageG
            << ", "
            << (int)cell.averageB
            << ")  Bright="
            << cell.brightness
            << "  Change="
            << cell.change
            << "  Changed="
            << (cell.changed ? "YES" : "NO")
            << "\n";
    }

    std::cout
        << "========================\n";
}

GridBuilder& VisionManager::GetGridBuilder()
{
    return gridBuilder;
}