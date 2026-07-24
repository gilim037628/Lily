#include "Grids.h"
#include "imgui.h"

#include <cmath>
#include <iostream>

void GridBuilder::Build(
    const Frame& frame
)
{
    layers.clear();
    layers.reserve(5);

    CreateLayer(frame,1,1);
    CreateLayer(frame,2,2);
    CreateLayer(frame,5,5);
    CreateLayer(frame,10,10);
    CreateLayer(frame,20,20);

    std::cout
        << "[Grid] Layers : "
        << layers.size()
        << std::endl;
}

std::vector<GridLayer>&
GridBuilder::GetLayers()
{
    return layers;
}

const std::vector<GridLayer>&
GridBuilder::GetLayers() const
{
    return layers;
}

void GridBuilder::CreateLayer(
    const Frame& frame,
    int rows,
    int cols
)
{
    GridLayer layer;

    layer.rows = rows;
    layer.cols = cols;

    int cellWidth =
        frame.width / cols;

    int cellHeight =
        frame.height / rows;

    layer.cells.reserve(
        rows * cols
    );

    for(int y = 0; y < rows; y++)
    {
        for(int x = 0; x < cols; x++)
        {
            GridCell cell;

            cell.x = x * cellWidth;
            cell.y = y * cellHeight;

            cell.width = cellWidth;
            cell.height = cellHeight;

            AnalyzeCell(frame, cell);

            // ★ 이게 빠져있었음
            layer.cells.push_back(cell);
        }
    }

    layers.push_back(layer);
}

void GridBuilder::AnalyzeCell(
    const Frame& frame,
    GridCell& cell
)
{
    if(frame.pixels.empty())
        return;

    uint64_t sumR = 0;
    uint64_t sumG = 0;
    uint64_t sumB = 0;

    uint64_t count = 0;

    uint32_t hash = 5381;

    const int stride =
        frame.width * 4;

    int maxY =
        std::min(
            cell.y + cell.height,
            frame.height
        );

    int maxX =
        std::min(
            cell.x + cell.width,
            frame.width
        );

    for(int py = cell.y; py < maxY; py++)
    {
        for(int px = cell.x; px < maxX; px++)
        {
            int index =
                py * stride +
                px * 4;

            uint8_t b =
                frame.pixels[index];

            uint8_t g =
                frame.pixels[index + 1];

            uint8_t r =
                frame.pixels[index + 2];

            sumR += r;
            sumG += g;
            sumB += b;

            hash =
                ((hash << 5) + hash)
                + r + g + b;

            count++;
        }
    }

    if(count == 0)
        return;

    cell.averageR =
        static_cast<uint8_t>(
            sumR / count
        );

    cell.averageG =
        static_cast<uint8_t>(
            sumG / count
        );

    cell.averageB =
        static_cast<uint8_t>(
            sumB / count
        );

    cell.brightness =
        (
            cell.averageR +
            cell.averageG +
            cell.averageB
        ) / 3.0f;

    cell.hash = hash;
}

void ChangeDetector::Update(
    GridBuilder& grid
)
{
    auto& layers =
        const_cast<
            std::vector<GridLayer>&
        >(grid.GetLayers());

    //----------------------------------
    // First Frame
    //----------------------------------

    if(firstFrame)
    {
        previousLayers = layers;
        firstFrame = false;
        return;
    }

    //----------------------------------
    // Compare
    //----------------------------------

    for(size_t l = 0;
        l < layers.size();
        l++)
    {
        auto& current =
            layers[l];

        auto& previous =
            previousLayers[l];

        for(size_t i = 0;
            i < current.cells.size();
            i++)
        {
            auto& now =
                current.cells[i];

            auto& old =
                previous.cells[i];

            float diff =
                std::abs(
                    (float)now.brightness -
                    (float)old.brightness
                );

            now.change =
                diff;

            now.changed =
                diff > 5.0f;
        }
    }

    previousLayers =
        layers;
}

bool DesktopCapture::Initialize()
{
    std::cout
        << "[Vision] DesktopCapture Initialized\n";

    return true;
}

bool DesktopCapture::Capture(
    Frame& frame
)
{
    frame.width = 1920;
    frame.height = 1080;

    frame.pixels.resize(
        frame.width
        * frame.height
        * 4,
        0
    );

    return true;
}

GridLayer& GridBuilder::GetLayer(
    int index
)
{
    return layers.at(index);
}

const GridLayer& GridBuilder::GetLayer(
    int index
) const
{
    return layers.at(index);
}

int GridBuilder::GetLayerCount() const
{
    return static_cast<int>(
        layers.size()
    );
}

GridCell& GridBuilder::GetCell(
    int layer,
    int row,
    int col
)
{
    GridLayer& l = layers.at(layer);

    if (row < 0 || row >= l.rows)
        throw std::out_of_range("row");

    if (col < 0 || col >= l.cols)
        throw std::out_of_range("col");

    return l.cells.at(row * l.cols + col);
}

const GridCell& GridBuilder::GetCell(
    int layer,
    int row,
    int col
) const
{
    const GridLayer& l = layers.at(layer);

    if (row < 0 || row >= l.rows)
        throw std::out_of_range("row");

    if (col < 0 || col >= l.cols)
        throw std::out_of_range("col");

    return l.cells.at(row * l.cols + col);
}

GridCell* GridBuilder::GetCellFromScreen(
    int layer,
    int x,
    int y
)
{
    GridLayer& l =
        layers.at(layer);

    for(auto& cell : l.cells)
    {
        if(
            x >= cell.x &&
            x < cell.x + cell.width &&
            y >= cell.y &&
            y < cell.y + cell.height
        )
        {
            return &cell;
        }
    }

    return nullptr;
}

const GridCell* GridBuilder::GetCellFromScreen(
    int layer,
    int x,
    int y
) const
{
    const GridLayer& l =
        layers.at(layer);

    for(const auto& cell : l.cells)
    {
        if(
            x >= cell.x &&
            x < cell.x + cell.width &&
            y >= cell.y &&
            y < cell.y + cell.height
        )
        {
            return &cell;
        }
    }

    return nullptr;
}

void GridRenderer::Render(
    const GridBuilder& grid,
    int layerIndex
)
{
    const GridLayer& layer =
        grid.GetLayer(layerIndex);

    ImDrawList* draw =
        ImGui::GetForegroundDrawList();

    for (const auto& cell : layer.cells)
    {
        ImU32 color =
            cell.changed
            ? IM_COL32(255,0,0,255)
            : IM_COL32(120,120,120,120);

        draw->AddRect(
            ImVec2(
                (float)cell.x,
                (float)cell.y
            ),
            ImVec2(
                (float)(cell.x+cell.width),
                (float)(cell.y+cell.height)
            ),
            color
        );
    }
}

class ObjectDetector
{
public:

    void Detect(
        const GridBuilder& grid
    );

    const std::vector<VisionObject>&
    GetObjects() const;

private:

    std::vector<VisionObject> objects;
};

