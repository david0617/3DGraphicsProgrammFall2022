#include "GameState.h"

using namespace BobEngine;
using namespace BobEngine::Graphics;
using namespace BobEngine::Math;
using namespace BobEngine::Input;

void GameState::Initialize()
{
	mCamera.SetPosition({ 0.0f, 1.0f, -4.0f });
	mCamera.SetLookAt({ 0.0f, 0.0f, 0.0f });

	mDirectionalLight.direction = Math::Normalize({ 1.0f, -1.0f, 1.0f });
	mDirectionalLight.ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
	mDirectionalLight.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	mDirectionalLight.specular = { 1.0f, 1.0f, 1.0f, 1.0f };

	mStandardEffect.Initialize(L"../../Assets/Shaders/Standard.fx");
	mStandardEffect.SetCamera(mCamera);
	mStandardEffect.setDirectionalLight(mDirectionalLight);

	mPostProcessingEffect.Initialize(L"../../Assets/Shaders/PostProcess.fx");
	mPostProcessingEffect.SetTexture(&mRenderTarget);

	GraphicsSystem* gs = GraphicsSystem::Get();
	const uint32_t screenWidth = gs->GetBackBufferWidth();
	const uint32_t screenHight = gs->GetBackBufferHeight();
	mRenderTarget.Initialize(screenWidth, screenHight, RenderTarget::Format::RGBA_U8);


	ModelId modelId = ModelManager::Get()->LoadModel(L"../../Assets/Models/Vanguard/character.model");
	mVanguard = CreateRenderGroup(modelId);
	for (auto& renderObject : mVanguard)
	{
		renderObject.transform.position.x = -2.0f;
	}

	modelId = ModelManager::Get()->LoadModel(L"../../Assets/Models/TY/character.model");
	mTY = CreateRenderGroup(modelId);
	for (auto& renderObject : mTY)
	{
		renderObject.transform.position.x = 2.0f;
	}

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(20, 20, 1.0f);
	mGround.meshBuffer.Initialize(groundMesh);
	mGround.diffuseMapId = TextureManager::Get()->LoadTexture(L"misc/concrete.jpg");

	MeshPX screenMesh = MeshBuilder::CreatScreenQuad();
	mScreenQuad.meshBuffer.Initialize(screenMesh);
}
void GameState::Terminate()
{
	mScreenQuad.Terminate();
	mGround.Terminate();
	CleanupRenderGroup(mTY);
	CleanupRenderGroup(mVanguard);
	mRenderTarget.Terminate();
	mPostProcessingEffect.Terminate();
    mStandardEffect.Terminate();
}
void GameState::Update(float deltaTime)
{
    UpdateCameraControl(deltaTime);
}
void GameState::Render()
{
	mRenderTarget.BeginRender();
		mStandardEffect.Begin();
			DrawRenderGroup(mStandardEffect, mVanguard);
			DrawRenderGroup(mStandardEffect, mTY);
			mStandardEffect.Render(mGround);
		mStandardEffect.End();
	mRenderTarget.EndRender();

	mPostProcessingEffect.Begin();
		mPostProcessingEffect.Render(mScreenQuad);
	mPostProcessingEffect.End();
}
void GameState::DebugUI()
{
	ImGui::Begin("Debug Control", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::CollapsingHeader("Light", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction", &mDirectionalLight.direction.x, 0.01f))
		{
			mDirectionalLight.direction = Math::Normalize(mDirectionalLight.direction);
		}
		ImGui::ColorEdit4("Ambient##Light", &mDirectionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &mDirectionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &mDirectionalLight.specular.r);
	}
	mStandardEffect.DebugUI();
	ImGui::End();
}

void GameState::UpdateCameraControl(float deltaTime)
{
	auto input = Input::InputSystem::Get();
	const float moveSpeed = input->IsKeyDown(KeyCode::LSHIFT) ? 10.0f : 1.0f;
	const float turnSpeed = 0.1f;

	if (input->IsKeyDown(KeyCode::W))
	{
		mCamera.Walk(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::S))
	{
		mCamera.Walk(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::D))
	{
		mCamera.Strafe(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::A))
	{
		mCamera.Strafe(-moveSpeed * deltaTime);
	}
	if (input->IsKeyDown(KeyCode::E))
	{
		mCamera.Rise(moveSpeed * deltaTime);
	}
	else if (input->IsKeyDown(KeyCode::Q))
	{
		mCamera.Rise(-moveSpeed * deltaTime);
	}
	if (input->IsMouseDown(MouseButton::RBUTTON))
	{
		mCamera.Yaw(input->GetMouseMoveX() * turnSpeed * deltaTime);
		mCamera.Pitch(input->GetMouseMoveY() * turnSpeed * deltaTime);
	}
}