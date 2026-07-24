#include <GLFW/glfw3.h>
#include <filesystem>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"

#include "UI/MainWindow.h"
#include "Vision/VisionManager.h"
#include "Engine/UpdateManager.h"

#include <iostream>

int main()
{
    glfwInit();

    GLFWwindow* window =
        glfwCreateWindow(
            1280,
            720,
            "Lily",
            nullptr,
            nullptr
        );

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();

    ImGui::CreateContext();

    ImGuiIO& io =
        ImGui::GetIO();

    ImFont* mainFont =
        io.Fonts->AddFontFromFileTTF(
            "assets/fonts/Pretendard-Regular.otf",
            22.0f,
            nullptr,
            io.Fonts->GetGlyphRangesKorean()
        );

    ImGui::StyleColorsDark();

    ImGui::GetStyle().ScaleAllSizes(1.35f);

    ImGui_ImplGlfw_InitForOpenGL(
        window,
        true
    );

    ImGui_ImplOpenGL2_Init();

    //----------------------------------
    // Managers
    //----------------------------------

    VisionManager vision;
    vision.Initialize();

    MainWindow mainWindow;

    mainWindow
        .GetRuntime()
        .Initialize();

    UpdateManager updater;

    updater.Initialize(
        &vision,
        &mainWindow
    );

    //----------------------------------
    // Main Loop
    //----------------------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        if(mainFont)
            ImGui::PushFont(mainFont);

        //----------------------------------
        // Update
        //----------------------------------

        updater.Update();

        if(mainFont)
            ImGui::PopFont();

        ImGui::Render();

        int display_w;
        int display_h;

        glfwGetFramebufferSize(
            window,
            &display_w,
            &display_h
        );

        glViewport(
            0,
            0,
            display_w,
            display_h
        );

        glClearColor(
            0.10f,
            0.10f,
            0.12f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT
        );

        ImGui_ImplOpenGL2_RenderDrawData(
            ImGui::GetDrawData()
        );

        glfwSwapBuffers(window);
    }

    //----------------------------------
    // Shutdown
    //----------------------------------

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}