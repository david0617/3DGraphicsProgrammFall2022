#pragma once
#include <BobEngine/Inc/BobEngine.h>

using namespace BobEngine;
using namespace BobEngine::Graphics;

class GameState : public BobEngine::AppState
{
public:
	enum class ShapeType
	{
		Transform,
		Sphere,
		AABB,
		AABBFilled,
		Custom,
		Count
	};
	virtual ~GameState() = default;

	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void UpdateCameraControl(float deltaTime);

	Camera mCamera;
	ShapeType mShapeType = ShapeType::Transform;
	float mSphereRadius = 1.0f;
	Color mShapeColor = Colors::BlueViolet;
};