#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"

namespace BobEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate()
		{
			meshBuffer.Terminate();
			diffuseMapId = 0;
			normalMapId = 0;
		}

		Transform transform;
		MeshBuffer meshBuffer;
		TextureId diffuseMapId;
		TextureId normalMapId;
	};
}