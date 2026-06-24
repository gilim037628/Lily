#include "HeaderBar.h"

#include <imgui.h>

void HeaderBar::Render()
{
    ImGui::Text("Lily");

    ImGui::SameLine();

    ImGui::TextColored(
        ImVec4(
            0.2f,
            1.0f,
            0.2f,
            1.0f
        ),
        "Running"
    );

    ImGui::Separator();
}