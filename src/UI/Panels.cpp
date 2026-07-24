#include "Panels.h"

#include <imgui.h>

#include "../Runtime/RuntimeManager.h"

AgentSidebar::AgentSidebar()
{
    agents.push_back(
    {
        "Lily",
        AIState::Running
    });

    agents.push_back(
    {
        "Minecraft Dev",
        AIState::Running
    });

    agents.push_back(
    {
        "Research AI",
        AIState::Background
    });

    agents.push_back(
    {
        "Artist",
        AIState::Stopped
    });
}

void AgentSidebar::Render()
{
    ImGui::Text("AI Manager");

    ImGui::Separator();

    //--------------------------------
    // Running
    //--------------------------------

    ImGui::Text("Running");

    for(size_t i = 0; i < agents.size(); i++)
    {
        if(agents[i].state != AIState::Running)
        {
            continue;
        }

        ImGui::PushID((int)i);

        bool selected =
            selectedAI == (int)i;

        std::string id =
            agents[i].name + "##" + std::to_string(i);

        if(
            ImGui::Selectable(
                id.c_str(),
                selected
            )
        )
        {
            selectedAI = (int)i;
        }

        if(
            ImGui::BeginPopupContextItem()
        )
        {
            if(
                ImGui::MenuItem(
                    "Move To Background"
                )
            )
            {
                agents[i].state =
                    AIState::Background;
            }

            if(
                ImGui::MenuItem(
                    "Stop"
                )
            )
            {
                agents[i].state =
                    AIState::Stopped;
            }

            ImGui::EndPopup();
        }

        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Separator();

    //--------------------------------
    // Background
    //--------------------------------

    ImGui::Text("Background");

    for(size_t i = 0; i < agents.size(); i++)
    {
        if(agents[i].state != AIState::Background)
        {
            continue;
        }

        ImGui::PushID((int)i);

        bool selected =
            selectedAI == (int)i;

        std::string id =
            agents[i].name + "##" + std::to_string(i);

        if(
            ImGui::Selectable(
                id.c_str(),
                selected
            )
        )
        {
            selectedAI = (int)i;
        }

        if(
            ImGui::BeginPopupContextItem()
        )
        {
            if(
                ImGui::MenuItem(
                    "Move To Running"
                )
            )
            {
                agents[i].state =
                    AIState::Running;
            }

            if(
                ImGui::MenuItem(
                    "Stop"
                )
            )
            {
                agents[i].state =
                    AIState::Stopped;
            }

            ImGui::EndPopup();
        }

        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Separator();

    //--------------------------------
    // Stopped
    //--------------------------------

    ImGui::Text("Stopped");

    for(size_t i = 0; i < agents.size(); i++)
    {
        if(agents[i].state != AIState::Stopped)
        {
            continue;
        }

        ImGui::PushID((int)i);

        bool selected =
            selectedAI == (int)i;

        std::string id =
            agents[i].name + "##" + std::to_string(i);

        if(
            ImGui::Selectable(
                id.c_str(),
                selected
            )
        )
        {
            selectedAI = (int)i;
        }

        if(
            ImGui::BeginPopupContextItem()
        )
        {
            if(
                ImGui::MenuItem(
                    "Move To Running"
                )
            )
            {
                agents[i].state =
                    AIState::Running;
            }

            if(
                ImGui::MenuItem(
                    "Move To Background"
                )
            )
            {
                agents[i].state =
                    AIState::Background;
            }

            ImGui::EndPopup();
        }

        ImGui::PopID();
    }

    ImGui::Spacing();
    ImGui::Separator();

    //--------------------------------
    // Create AI
    //--------------------------------

    if(
        ImGui::Button(
            "+ Create AI",
            ImVec2(-1, 40)
        )
    )
    {
        agents.push_back(
        {
            "New AI",
            AIState::Stopped
        });
    }
}

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

void StatusBar::Render()
{
    ImGui::Separator();

    ImGui::Text(
        "CPU 3% | RAM 2.1GB | Voice ON | Live2D OFF"
    );
}

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