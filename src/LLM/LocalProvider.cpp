#include "LocalProvider.h"

LocalProvider::LocalProvider()
{
}

std::string LocalProvider::Generate(
    const std::string& prompt
)
{
    return "[LOCAL] " + prompt;
}