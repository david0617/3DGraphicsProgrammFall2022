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

    mVertexShader.Initialize<Vertex>(filepath);
    mPixelShader.Initialize(filepath);
    mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}
void StandardEffect::Terminate()
{
    mSampler.Terminate();
    mPixelShader.Terminate();
    mVertexShader.Terminate();
    mTransformBuffer.Terminate();
}
void StandardEffect::Begin()
{

}
void StandardEffect::end()
{
    // nething for now (shadows)
}
void StandardEffect::Render(const RenderObject& renderObject)
{

}
void StandardEffect::SetCamera(const Camera& camera)
{
    mCamera = &camera;
}
void StandardEffect::DebugUI()
{

}