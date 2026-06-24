#include "ViewPanel.h"

#include "../Runtime/RuntimeManager.h"

#include <imgui.h>

void ViewPanel::Render(
    RuntimeManager& runtime
)
{
    ImGui::Text(
        "Lily AI Test"
    );

    ImGui::Separator();

    ImGui::InputTextMultiline(
        "##Prompt",
        promptBuffer,
        sizeof(promptBuffer),
        ImVec2(-1, 120)
    );

    if(
        ImGui::Button(
            "Send"
        )
    )
    {
        response =
            runtime.Generate(
                promptBuffer
            );
    }

    ImGui::Spacing();

    ImGui::Text(
        "Response"
    );

    ImGui::Separator();

    ImGui::TextWrapped(
        "%s",
        response.c_str()
    );
}