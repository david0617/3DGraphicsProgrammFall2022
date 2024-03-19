#include "Precompiled.h"
#include "RenderObject.h"

using namespace BobEngine;
using namespace BobEngine::Graphics;

void RenderObject::Terminate()
{
    meshBuffer.Terminate();
    diffuseMapId = 0;
    normalMapId = 0;
    specMapId = 0;
    bumpMapId = 0;
}
RenderGroup BobEngine::Graphics::CreateRenderGroup(ModelId id)
{
    const Model* model = ModelManager::Get()->GetModel(id);
    ASSERT(model != nullptr, "RenderGroup: ModelID %d is not loaded", id);
    RenderGroup renderGroup = CreateRenderGroup(*model);
    for (RenderObject& renderObject : renderGroup)
    {
        renderObject.modelId = id;
    }
    return renderGroup;
}
RenderGroup Graphics::CreateRenderGroup(const Model& model)
{
    RenderGroup renderGroup;
    renderGroup.resize(model.meshData.size());
    for (const Model::MeshData& meshData : model.meshData)
    {
        RenderObject& renderObject = renderGroup.emplace_back();
        renderObject.meshBuffer.Initialize(meshData.mesh);
    }
    return renderGroup;
}
void Graphics::CleanupRenderGroup(RenderGroup& renderGroup)
{
    for (RenderObject& renderObject : renderGroup)
    {
        renderObject.Terminate();
    }
}