#pragma once
#include <BobEngine/Inc/BobEngine.h>

using namespace BobEngine;
using namespace BobEngine::Graphics;
using namespace BobEngine::Math;

class GameState : public BobEngine::AppState
{
public:
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void UpdateCameraControl(float deltaTime);

	Camera mCamera;
	DirectionalLight mDirectionalLight;
	Mesh mSphere;
	RenderObject mEarth;
	StandardEffect mStandardEffect;

	Camera mRenderTargetCamera;
	RenderTarget mRenderTarget;

	bool mUseCelshading = false;
	StandardEffect mCelShadingEffect;
};