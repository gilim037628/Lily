#include <GLFW/glfw3.h>
#include <filesystem>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl2.h"

#include "UI/MainWindow.h"
#include "Runtime/RuntimeManager.h"

#include <iostream>

int main()
{
    std::cout << "[1] Program Start\n";

    // GLFW 초기화
    if (!glfwInit())
    {
        std::cout << "[FAIL] glfwInit\n";
        return -1;
    }

    std::cout << "[2] GLFW Initialized\n";

    // 창 생성
    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "Lily",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cout << "[FAIL] Window Create\n";

        glfwTerminate();
        return -1;
    }

    std::cout << "[3] Window Created\n";

    glfwMakeContextCurrent(window);

    std::cout << "[4] OpenGL Context Ready\n";

    // VSync
    glfwSwapInterval(1);

    std::cout << "[5] VSync Enabled\n";

    IMGUI_CHECKVERSION();

    std::cout << "[6] ImGui Version OK\n";

    ImGui::CreateContext();

    std::cout << "[7] ImGui Context Created\n";

    std::cout
        << "Current Path: "
        << std::filesystem::current_path()
        << std::endl;

    ImGuiIO& io = ImGui::GetIO();

    std::cout << "[8] ImGuiIO Ready\n";

    // 폰트
    ImFont* mainFont = io.Fonts->AddFontFromFileTTF(
        "assets/fonts/Pretendard-Regular.otf",
        22.0f,
        nullptr,
        io.Fonts->GetGlyphRangesKorean()
    );

    if(mainFont)
    {
        std::cout << "[9] Font Loaded\n";
    }
    else
    {
        std::cout << "[9] Font FAILED\n";
    }

    ImGui::StyleColorsDark();

    std::cout << "[10] Style Applied\n";

    ImGui::GetStyle().ScaleAllSizes(1.35f);

    std::cout << "[11] UI Scale Applied\n";

    ImGui_ImplGlfw_InitForOpenGL(
        window,
        true
    );

    std::cout << "[12] ImGui GLFW Backend Ready\n";

    ImGui_ImplOpenGL2_Init();

    std::cout << "[13] ImGui OpenGL2 Backend Ready\n";

    // RuntimeManager runtime;
    // runtime.Initialize();
    // runtime.LoadModel(
    //     "models/llm/Qwen3-4B-ONNX/onnx/model_q4f16.onnx"
    // );

    std::cout << "[14] Before MainWindow\n";

    MainWindow mainWindow;

    std::cout << "[15] MainWindow Created\n";

        std::cout
        << "[15.1] Runtime Init\n";

    mainWindow
        .GetRuntime()
        .Initialize();

    std::cout
        << "[15.2] Load Model\n";

    mainWindow
        .GetRuntime()
        .LoadModel(
            R"(C:\Users\dev\LilyV1\models\llm\Qwen3-4B-ONNX\onnx\model_q4f16.onnx)"
        );

    while (!glfwWindowShouldClose(window))
    {
        static bool firstFrame = true;

        if(firstFrame)
        {
            std::cout << "[16] Enter Main Loop\n";
            firstFrame = false;
        }

        glfwPollEvents();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        if(mainFont)
        {
            ImGui::PushFont(mainFont);
        }

        mainWindow.Render();

        if(mainFont)
        {
            ImGui::PopFont();
        }

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

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(
            ImGui::GetDrawData()
        );

        glfwSwapBuffers(window);
    }

    std::cout << "[17] Main Loop Exit\n";

    ImGui_ImplOpenGL2_Shutdown();

    std::cout << "[18] OpenGL2 Shutdown\n";

    ImGui_ImplGlfw_Shutdown();

    std::cout << "[19] GLFW Backend Shutdown\n";

    ImGui::DestroyContext();

    std::cout << "[20] ImGui Destroyed\n";

    glfwDestroyWindow(window);

    glfwTerminate();

    std::cout << "[21] Program End\n";

    return 0;
}