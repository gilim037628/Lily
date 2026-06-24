#include "MainWindow.h"

#include <imgui.h>
#include <iostream>

MainWindow::MainWindow()
{
    std::cout
        << "MAINWINDOW CREATED\n";
}

RuntimeManager&
MainWindow::GetRuntime()
{
    return runtime;
}

void MainWindow::Render()
{
    ImGuiIO& io =
        ImGui::GetIO();

    //---------------------------------
    // 애니메이션
    //---------------------------------

    float targetLeft =
        showAgentPanel ?
        320.0f :
        0.0f;

    float targetRight =
        showSettingsPanel ?
        420.0f :
        0.0f;

    leftWidth +=
        (targetLeft - leftWidth)
        * 0.12f;

    rightWidth +=
        (targetRight - rightWidth)
        * 0.12f;

    //---------------------------------
    // 메인 Root
    //---------------------------------

    ImGui::SetNextWindowPos(
        ImVec2(0, 0)
    );

    ImGui::SetNextWindowSize(
        io.DisplaySize
    );

    ImGui::Begin(
        "LilyRoot",
        nullptr,

        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoBringToFrontOnFocus
    );

    //---------------------------------
    // Header
    //---------------------------------

    headerBar.Render();

    //---------------------------------
    // View
    //---------------------------------

    viewPanel.Render(
        runtime
    );

    //---------------------------------
    // Status
    //---------------------------------

    statusBar.Render();

    //---------------------------------
    // 왼쪽 토글 버튼
    //---------------------------------

    ImGui::SetCursorScreenPos(
        ImVec2(
            leftWidth,
            io.DisplaySize.y * 0.5f - 25
        )
    );

    if(
        ImGui::Button(
            showAgentPanel ?
            "<##left<toggle" :
            ">##left>toggle",
            ImVec2(40, 50)
        )
    )
    {
        showAgentPanel =
            !showAgentPanel;
    }

    //---------------------------------
    // 오른쪽 토글 버튼
    //---------------------------------

    ImGui::SetCursorScreenPos(
        ImVec2(
            io.DisplaySize.x
            - rightWidth
            - 40,

            io.DisplaySize.y * 0.5f - 25
        )
    );

    if(
        ImGui::Button(
            showSettingsPanel ?
            ">##right>toggle" :
            "<##right<toggle",
            ImVec2(40, 50)
        )
    )
    {
        showSettingsPanel =
            !showSettingsPanel;
    }

    ImGui::End();

    //---------------------------------
    // Agent Sidebar
    //---------------------------------

    if(leftWidth > 1.0f)
    {
        ImGui::SetNextWindowPos(
            ImVec2(
                0,
                0
            )
        );

        ImGui::SetNextWindowSize(
            ImVec2(
                leftWidth,
                io.DisplaySize.y
            )
        );

        ImGui::Begin(
            "AgentSidebarWindow",
            nullptr,

            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );

        agentSidebar.Render();

        ImGui::End();
    }

    //---------------------------------
    // Settings Sidebar
    //---------------------------------

    if(rightWidth > 1.0f)
    {
        ImGui::SetNextWindowPos(
            ImVec2(
                io.DisplaySize.x
                - rightWidth,
                0
            )
        );

        ImGui::SetNextWindowSize(
            ImVec2(
                rightWidth,
                io.DisplaySize.y
            )
        );

        ImGui::Begin(
            "SettingsWindow",
            nullptr,

            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove
        );

        settingsSidebar.Render(
            runtime.GetMemoryManager()
        );
        ImGui::End();
    }
}