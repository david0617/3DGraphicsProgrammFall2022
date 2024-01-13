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
	void DebugUI() override;

private:
	void UpdateCameraControl(float deltaTime);

	Camera mCamera;
	RenderObject mRenderObject;
	RenderObject mRenderObject2;
	SimpleEffect mSimpleEffect;

	Camera mRenderTargetCamera;
	SimpleEffect mRenderTargetSimpleEffect;
	RenderTarget mRenderTarget;
};