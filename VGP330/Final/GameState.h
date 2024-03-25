#pragma once
#include <BobEngine/Inc/BobEngine.h>

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

	BobEngine::Graphics::Camera mCamera;
	BobEngine::Graphics::DirectionalLight mDirectionalLight;
	BobEngine::Graphics::StandardEffect mStandardEffect;
	BobEngine::Graphics::PostProcessingEffect mPostProcessingEffect;
	BobEngine::Graphics::GaussianBlurEffect mGaussianBlurEffect;

	BobEngine::Graphics::RenderGroup mVanguard;
	BobEngine::Graphics::RenderGroup mTY;
	BobEngine::Graphics::RenderObject mGround;
	BobEngine::Graphics::RenderObject mScreenQuad;

	BobEngine::Graphics::RenderTarget mRenderTarget;
	BobEngine::Graphics::RenderTarget mBlurRenderTarget;
};