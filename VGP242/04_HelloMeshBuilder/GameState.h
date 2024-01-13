#pragma once
#include <BobEngine/Inc/BobEngine.h>

using namespace BobEngine;
using namespace BobEngine::Graphics;

class GameState : public BobEngine::AppState
{
public:
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;

protected:
	Camera mCamera;
	ConstantBuffer mConstantBuffer;
	MeshBuffer mMeshBuffer;
	VertexShader mVertexShader;
	PixelShader mPixelShader;

	Texture mDiffuseTexture;
	Sampler mSampler;
};