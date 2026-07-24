#pragma once

#include <memory>

#include "Grids.h"

class VisionManager
{
public:

    bool Initialize();

    void Update();

    GridBuilder& GetGridBuilder();

private:

    std::unique_ptr<ICaptureSource> capture;

    GridBuilder gridBuilder;

    Frame frame;

    ChangeDetector changeDetector;
};