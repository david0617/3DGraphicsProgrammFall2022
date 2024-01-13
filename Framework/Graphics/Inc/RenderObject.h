#pragma once

#include "MeshBuffer.h"
#include "Transform.h"
#include "Texture.h"

namespace BobEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate()
		{
			meshBuffer.Terminate();
			mDiffuseTexture.Terminate();
		}

		Transform transform;
		MeshBuffer meshBuffer;
		Texture mDiffuseTexture;
	};
}