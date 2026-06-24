#include "SettingsSidebar.h"

#include <imgui.h>

void SettingsSidebar::Render(
    MemoryManager& memory
)
{
    //--------------------------------
    // 왼쪽 탭
    //--------------------------------

    ImGui::BeginChild(
        "TabList",
        ImVec2(140, 0),
        true
    );

    const char* tabs[] =
    {
        "GENERAL",
        "AI",
        "VOICE",
        "LIVE2D",
        "MEMORY",
        "AUTONOMY",
        "ADVANCED"
    };

    for(int i = 0; i < 7; i++)
    {
        if(
            ImGui::Selectable(
                tabs[i],
                selectedTab == i
            )
        )
        {
            selectedTab = i;
        }
    }

    ImGui::EndChild();

    ImGui::SameLine();

    //--------------------------------
    // 내용
    //--------------------------------

    ImGui::BeginChild(
        "SettingsContent",
        ImVec2(0,0),
        true
    );

    switch(selectedTab)
    {
        //--------------------------------
        // GENERAL
        //--------------------------------

        case 0:
        {
            static bool korean = true;

            ImGui::Text("Language");
            ImGui::Separator();

            ImGui::Checkbox(
                "Use Korean",
                &korean
            );

            break;
        }

        //--------------------------------
        // AI
        //--------------------------------

        case 1:
        {
            static float temperature = 0.7f;
            static float topP = 0.9f;

            ImGui::Text("Model");

            ImGui::Separator();

            ImGui::Text(
                "Current : Qwen3-4B"
            );

            ImGui::Spacing();

            ImGui::SliderFloat(
                "Temperature",
                &temperature,
                0.0f,
                2.0f
            );

            ImGui::SliderFloat(
                "TopP",
                &topP,
                0.0f,
                1.0f
            );

            break;
        }

        //--------------------------------
        // VOICE
        //--------------------------------

        case 2:
        {
            static bool ttsEnabled = true;
            static bool voiceInput = true;

            ImGui::Text("Voice");

            ImGui::Separator();

            ImGui::Checkbox(
                "Enable TTS",
                &ttsEnabled
            );

            ImGui::Checkbox(
                "Enable Voice Input",
                &voiceInput
            );

            break;
        }

        //--------------------------------
        // LIVE2D
        //--------------------------------

        case 3:
        {
            static bool live2dEnabled = true;
            static bool live2dMove = true;
            static bool live2dRotate = false;

            ImGui::Text("Live2D");

            ImGui::Separator();

            ImGui::Checkbox(
                "Enable Live2D",
                &live2dEnabled
            );

            ImGui::Checkbox(
                "Allow Move",
                &live2dMove
            );

            ImGui::Checkbox(
                "Allow Rotate",
                &live2dRotate
            );

            break;
        }

        //--------------------------------
        // MEMORY
        //--------------------------------

        case 4:
        {
            ImGui::Text(
                "Memory"
            );

            ImGui::Separator();

            ImGui::Text(
                "Long Memory Count : %d",
                (int)memory.GetLongMemory().size()
            );

            ImGui::Text(
                "Short Memory Count : %d",
                (int)memory.GetShortMemory().size()
            );

            ImGui::Spacing();

            if(
                ImGui::Button(
                    "Clear Short Memory"
                )
            )
            {
                memory.ClearShortMemory();
            }

            ImGui::Spacing();

            if(
                ImGui::Button(
                    "Open Memory Editor"
                )
            )
            {
                ImGui::OpenPopup(
                    "LongMemoryEditor"
                );
            }

            //--------------------------------
            // Memory Editor Popup
            //--------------------------------

            if(
                ImGui::BeginPopupModal(
                    "LongMemoryEditor",
                    nullptr
                )
            )
            {
                ImGui::Text(
                    "Long Memory"
                );

                ImGui::Separator();

                ImGui::BeginChild(
                    "MemoryList",
                    ImVec2(
                        700,
                        350
                    ),
                    true
                );

                const auto& memories =
                    memory.GetLongMemory();

                for(
                    const auto& entry
                    : memories
                )
                {
                    ImGui::Text(
                        "[%s]",
                        ToString(
                            entry.category
                        )
                    );

                    ImGui::SameLine();

                    ImGui::TextWrapped(
                        "%s",
                        entry.content.c_str()
                    );

                    ImGui::Separator();
                }

                ImGui::EndChild();

                if(
                    ImGui::Button(
                        "Close"
                    )
                )
                {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            break;
        }

        //--------------------------------
        // AUTONOMY
        //--------------------------------

        case 5:
        {
            static bool selfTalk = true;
            static bool internetAccess = false;
            static bool gameControl = false;

            ImGui::Text(
                "Autonomy"
            );

            ImGui::Separator();

            ImGui::Checkbox(
                "Allow Self Talk",
                &selfTalk
            );

            ImGui::Checkbox(
                "Allow Internet Access",
                &internetAccess
            );

            ImGui::Checkbox(
                "Allow Game Control",
                &gameControl
            );

            break;
        }

        //--------------------------------
        // ADVANCED
        //--------------------------------

        case 6:
        {
            static bool debugMode = false;

            ImGui::Text(
                "Advanced"
            );

            ImGui::Separator();

            ImGui::Checkbox(
                "Debug Mode",
                &debugMode
            );

            if(
                ImGui::Button(
                    "Reload Runtime"
                )
            )
            {
            }

            break;
        }
    }

    ImGui::EndChild();
}