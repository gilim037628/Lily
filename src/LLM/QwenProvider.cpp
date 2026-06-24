#include "QwenProvider.h"

#include <onnxruntime_cxx_api.h>

#include <iostream>

static Ort::Env g_env(
    ORT_LOGGING_LEVEL_WARNING,
    "Lily"
);

static std::unique_ptr<Ort::Session>
    g_session;

bool QwenProvider::Initialize(
    const std::string& modelPath
)
{
    try
    {
        Ort::SessionOptions options;

        options.SetIntraOpNumThreads(4);

        g_session =
            std::make_unique<
                Ort::Session
            >(
                g_env,
                std::wstring(
                    modelPath.begin(),
                    modelPath.end()
                ).c_str(),
                options
            );

        initialized = true;

        Ort::AllocatorWithDefaultOptions allocator;

        size_t inputCount =
            g_session->GetInputCount();

        std::cout
            << "\n===== INPUTS =====\n";

        for(size_t i = 0; i < inputCount; i++)
        {
            auto name =
                g_session->GetInputNameAllocated(
                    i,
                    allocator
                );

            std::cout
                << i
                << " : "
                << name.get()
                << std::endl;
        }

        size_t outputCount =
            g_session->GetOutputCount();

        std::cout
            << "\n===== OUTPUTS =====\n";

        for(size_t i = 0; i < outputCount; i++)
        {
            auto name =
                g_session->GetOutputNameAllocated(
                    i,
                    allocator
                );

            std::cout
                << i
                << " : "
                << name.get()
                << std::endl;
        }

        std::cout
            << "[Qwen] Model Loaded\n";

        return true;
    }
    catch(const std::exception& e)
    {
        std::cout
            << "[Qwen] Load Failed : "
            << e.what()
            << std::endl;

        return false;
    }
}

std::string QwenProvider::Generate(
    const std::string& prompt
)
{
    if(!initialized)
    {
        return
            "[Qwen] Not Initialized";
    }

    return
        "[Qwen Loaded]\n" +
        prompt;
}