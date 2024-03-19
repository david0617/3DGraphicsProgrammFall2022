#pragma once

#include "Material.h"
#include "MeshBuffer.h"
#include "Transform.h"
#include "TextureManager.h"
#include "Model.h"
#include "ModelManager.h"

namespace BobEngine::Graphics
{
	class RenderObject
	{
	public:
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;
		
		ModelId modelId;
		Material material;
		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(ModelId id);
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model);
	void CleanupRenderGroup(RenderGroup& renderGroup);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (const RenderObject& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}