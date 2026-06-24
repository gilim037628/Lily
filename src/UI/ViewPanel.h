#pragma once

#include <string>

class RuntimeManager;

class ViewPanel
{
public:

    void Render(
        RuntimeManager& runtime
    );

private:

    char promptBuffer[1024] = "";

    std::string response;
};