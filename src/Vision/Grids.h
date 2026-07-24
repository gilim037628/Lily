#pragma once

#include <vector>
#include <cstdint>
#include <string>

struct Frame
{
    int width = 0;
    int height = 0;

    // BGRA 또는 RGBA
    std::vector<uint8_t> pixels;
};

struct GridCell
{
    int x = 0;
    int y = 0;

    int width = 0;
    int height = 0;

    //----------------------------------
    // Vision
    //----------------------------------

    float brightness = 0.f;

    uint8_t averageR = 0;
    uint8_t averageG = 0;
    uint8_t averageB = 0;

    uint32_t hash = 0;

    //----------------------------------
    // Motion
    //----------------------------------

    float change = 0.f;

    bool changed = false;
};

struct GridLayer
{
    int rows = 0;
    int cols = 0;

    std::vector<GridCell> cells;
};

class GridBuilder
{
public:

    //----------------------------------
    // Build
    //----------------------------------

    void Build(
        const Frame& frame
    );

    //----------------------------------
    // Layers
    //----------------------------------

    const std::vector<GridLayer>&
    GetLayers() const;

    std::vector<GridLayer>&
    GetLayers();

    GridLayer&
    GetLayer(
        int index
    );

    const GridLayer&
    GetLayer(
        int index
    ) const;

    int
    GetLayerCount() const;

    //----------------------------------
    // Cells
    //----------------------------------

    GridCell&
    GetCell(
        int layer,
        int row,
        int col
    );

    const GridCell&
    GetCell(
        int layer,
        int row,
        int col
    ) const;

    GridCell*
    GetCellFromScreen(
        int layer,
        int x,
        int y
    );

    const GridCell*
    GetCellFromScreen(
        int layer,
        int x,
        int y
    ) const;

private:

    //----------------------------------
    // Build
    //----------------------------------

    void CreateLayer(
        const Frame& frame,
        int cols,
        int rows
    );

    //----------------------------------
    // Analysis
    //----------------------------------

    void AnalyzeCell(
        const Frame& frame,
        GridCell& cell
    );

private:

    int frameWidth = 0;
    int frameHeight = 0;

    std::vector<GridLayer> layers;
};

class ChangeDetector
{
public:

    void Update(
        GridBuilder& grid
    );

private:

    bool firstFrame = true;

    std::vector<GridLayer> previousLayers;
};

class ICaptureSource
{
public:

    virtual ~ICaptureSource() = default;

    virtual bool Initialize() = 0;

    virtual bool Capture(
        Frame& frame
    ) = 0;
};

class DesktopCapture
    : public ICaptureSource
{
public:

    bool Initialize() override;

    bool Capture(
        Frame& frame
    ) override;
};

class CameraCapture
    : public ICaptureSource
{
public:

    bool Initialize() override
    {
        return true;
    }

    bool Capture(
        Frame& frame
    ) override
    {
        return false;
    }
};

class ImageCapture
    : public ICaptureSource
{
public:

    bool Initialize() override
    {
        return true;
    }

    bool Capture(
        Frame& frame
    ) override
    {
        return false;
    }
};

class VirtualDesktopCapture
    : public ICaptureSource
{
public:

    bool Initialize() override
    {
        return true;
    }

    bool Capture(
        Frame& frame
    ) override
    {
        return false;
    }
};

class WindowCapture
    : public ICaptureSource
{
public:

    bool Initialize() override
    {
        return true;
    }

    bool Capture(
        Frame& frame
    ) override
    {
        return false;
    }
};

class GridRenderer
{
public:

    void Render(
        const GridBuilder& grid,
        int layer
    );
};

struct VisionObject
{
    std::string label;

    int x = 0;
    int y = 0;

    int width = 0;
    int height = 0;

    float confidence = 0.f;
};