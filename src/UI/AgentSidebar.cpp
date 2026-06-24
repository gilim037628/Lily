#include "AgentSidebar.h"

#include <imgui.h>

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