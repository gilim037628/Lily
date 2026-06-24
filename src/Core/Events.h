#pragma once

#include <string>

struct UserInputEvent
{
    std::string text;
};

struct LLMResponseEvent
{
    std::string text;
};

struct TTSSpeakEvent
{
    std::string text;
};

struct EmotionEvent
{
    std::string emotion;
};