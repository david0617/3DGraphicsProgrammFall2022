#include "Precompiled.h"
#include "SimpleEffect.h"

#include "Camera.h"
#include "MeshBuffer.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace BobEngine;
using namespace BobEngine::Graphics;

void SimpleEffect::Initialize()
{
	std::filesystem::path filePath = L"../../Assets/Shaders/DoTexturing.fx";
	mVertexShader.Initialize<VertexPX>(filePath);
	mPixelShader.Initialize(filePath);
	mConstantBuffer.Initialize(sizeof(Math::Matrix4));
	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void SimpleEffect::Terminate()
{
	mSampler.Terminate();
	mConstantBuffer.Terminate();
	mPixelShader.Terminate();
	mVertexShader.Terminate();
}

void SimpleEffect::Begin()
{
	mVertexShader.Bind();
	mPixelShader.Bind();
	mConstantBuffer.BindVS(0);
	mSampler.BindPS(0);
}

void SimpleEffect::End()
{
	Texture::UnbindPS(0);
}

void SimpleEffect::Render(const RenderObject& renderObject)
{
	Math::Matrix4 matWorld = renderObject.transform.GetMatrix4();
	Math::Matrix4 matView = mCamera->GetViewMatrix();
	Math::Matrix4 matProj = mCamera->GetProjectionMatrix();
	Math::Matrix4 matFinal = matWorld * matView * matProj;
	Math::Matrix4 wvp = Transpose(matFinal);

	mConstantBuffer.Update(&wvp);
	
	renderObject.mDiffuseTexture.BindPS(0);
	renderObject.meshBuffer.Render();
}

void SimpleEffect::SetCamera(const Camera& camera)
{
	mCamera = &camera;
}
