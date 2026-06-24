#include "StatusBar.h"

#include <imgui.h>

void StatusBar::Render()
{
    ImGui::Separator();

    ImGui::Text(
        "CPU 3% | RAM 2.1GB | Voice ON | Live2D OFF"
    );
}