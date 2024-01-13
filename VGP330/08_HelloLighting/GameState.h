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
	Camera mCamera;
	Mesh mSphere;
	RenderObject mEarth;
	SimpleEffect mEffect;
};