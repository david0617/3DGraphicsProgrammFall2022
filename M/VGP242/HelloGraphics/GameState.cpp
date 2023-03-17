#include "GameState.h"
#include "Input/Inc/InputSystem.h"
#include <WinUser.h>


void GameState::Initialize() 
{
    M::Graphics::GraphicsSystem::Get()->SetClearColour(M::Colors::Black);
}

void GameState::Update(float deltaTime) 
{
    auto inputSystem = Input::InputSystem::Get();

    if (inputSystem->IsKeyPressed(Input::KeyCode::UP))
    {
        M::Graphics::GraphicsSystem::Get()->SetClearColour(M::Colors::Red);
    }
    else if (inputSystem->IsKeyPressed(Input::KeyCode::DOWN))
    {
        M::Graphics::GraphicsSystem::Get()->SetClearColour(M::Colors::Green);
    }
}