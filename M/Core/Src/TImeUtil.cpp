#include "Precompiled.h"
#include "../Inc/TimeUtil.h"

float M::Core::TimeUtil::GetTime()
{
    // get the difference since the start time
    static const auto startTime = std::chrono::high_resolution_clock::now();
    const auto currentTime = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast < std::chrono::microseconds > (currentTime - startTime).count();
    return milliseconds / 1000.f;
}

float M::Core::TimeUtil::GetDelaTime()
{
    // get the difference since the last time we checked
    static auto lastCallTime = std::chrono::high_resolution_clock::now();
    const auto currentTime = std::chrono::high_resolution_clock::now();
    const auto milliseconds = std::chrono::duration_cast <std::chrono::milliseconds>(currentTime - lastCallTime).count();
    lastCallTime = currentTime;
    return milliseconds / 1000.f;
}