#pragma once

#include "Colors.h"

namespace BobEngine::Graphics
{
	struct  Meaterial
	{
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		Color emissive = Colors::White;
		float power = 10.0f;
		float padding[3];
	};
}