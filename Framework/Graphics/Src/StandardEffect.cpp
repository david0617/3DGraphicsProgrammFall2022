#include "Precompiled.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace BobEngine;
using namespace BobEngine::Graphics;

void StandardEffect::Initialize(const std::filesystem::path& filepath)
{
    mTransformBuffer.Initialize();
    mLightBuffer.Initialize();

    mVertexShader.Initialize<Vertex>(filepath);
    mPixelShader.Initialize(filepath);
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}
void StandardEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mLightBuffer.Terminate();
    mTransformBuffer.Terminate();
}
void StandardEffect::Begin()
{
    ASSERT(mCamera != nullptr, "StandardEffect: no camera set");
    ASSERT(mDirectionalLight != nullptr, "StandardEffect: no light set");
    mVertexShader.Bind();
    mPixelShader.Bind();

    mTransformBuffer.BindVS(0);
    mLightBuffer.BindVS(1);
    mLightBuffer.BindPS(1);

    mSampler.BindPS(0);
}
void StandardEffect::End()
{
    // nething for now (shadows)
}
void StandardEffect::Render(const RenderObject& renderObject)
{
    const auto& matWorld = renderObject.transform.GetMatrix4();
    const auto& matView = mCamera->GetViewMatrix();
    const auto& matProj = mCamera->GetProjectionMatrix();

    Transformdata data;
    data.wvp = Transpose(matWorld * matView * matProj);
    data.world = Transpose(matWorld);
    data.viewPosition = mCamera->GetPosition();
    mTransformBuffer.Update(data);
    mLightBuffer.Update(*mDirectionalLight);

    auto tm = TextureManager::Get();
    tm->BindPS(renderObject.diffuseMapId, 0);
    tm->BindPS(renderObject.normalMapId, 1);
    renderObject.meshBuffer.Render();
}
void StandardEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}
void StandardEffect::setDirectionalLight(const DirectionalLight& directionalLight)
{
    mDirectionalLight = &directionalLight;
}
void StandardEffect::DebugUI()
{

}