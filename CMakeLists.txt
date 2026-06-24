cmake_minimum_required(VERSION 3.20)

project(Lily)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------
# GLFW
# ------------------------------------

add_subdirectory(thirdparty/glfw)

# ------------------------------------
# OpenGL
# ------------------------------------

find_package(OpenGL REQUIRED)

# ONNX Runtime

set(ONNXRUNTIME_DIR
    ${CMAKE_SOURCE_DIR}/thirdparty/onnxruntime
)

# ------------------------------------
# ImGui
# ------------------------------------

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/thirdparty/imgui)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp

    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui PUBLIC
    glfw
    OpenGL::GL
)

# ------------------------------------
# Lily
# ------------------------------------

add_executable(Lily
    src/main.cpp

    # UI
    src/UI/MainWindow.cpp
    src/UI/AgentSidebar.cpp
    src/UI/SettingsSidebar.cpp
    src/UI/ChatView.cpp
    src/UI/HeaderBar.cpp
    src/UI/StatusBar.cpp
    src/UI/ViewPanel.cpp

    # LLM
    src/LLM/LocalProvider.cpp
    src/LLM/AIManager.cpp
    src/LLM/QwenProvider.cpp
    src/LLM/QwenProvider.h

    # Character
    src/Character/CharacterManager.cpp

    # Prompt
    src/Prompt/PromptManager.cpp

    # Memory
    src/Memory/MemoryManager.cpp

    # Runtime
    src/Runtime/RuntimeManager.cpp
    src/Memory/MemoryAnalyzer.h
    src/Memory/MemoryAnalyzer.cpp
    src/Memory/MemoryCategory.cpp
)

target_include_directories(Lily PRIVATE
    src

    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
    ${ONNXRUNTIME_DIR}/include
)

target_link_libraries(Lily PRIVATE
    glfw
    imgui
    OpenGL::GL
    ${ONNXRUNTIME_DIR}/lib/onnxruntime.lib
)

add_custom_command(
    TARGET Lily POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Lily>/assets
)

add_custom_command(
    TARGET Lily POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/thirdparty/onnxruntime/lib/onnxruntime.dll"
    $<TARGET_FILE_DIR:Lily>
)

add_custom_command(
    TARGET Lily POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/thirdparty/onnxruntime/lib/onnxruntime_providers_shared.dll"
    $<TARGET_FILE_DIR:Lily>
)