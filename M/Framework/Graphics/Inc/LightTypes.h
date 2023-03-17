#pragma once
#include "Colours.h"

namespace M::Graphics
{
    struct DirectionalLight
    {
        MMath::Vector3 direction = MMath::Vector3::Zero;
        float padding = 0.0f;
        Color ambient = Colors::White;
        Color diffuse = Colors::White;
        Color specular = Colors::White;


    };
}