#include "GameState.h"
#include <WinUser.h>

void GameState::Initialize()
{
    M::Graphics::GraphicsSystem::Get()->SetClearColors(M::Colors::Black);
}

void GameState::Update(float deltaTime)
{
    if (GetAsyncKeyState(VK_NUMPAD1))
    {
        M::Graphics::GraphicsSystem::Get()->SetClearColors(M::Colors::Red);
    }
    else if (GetAsyncKeyState(VK_NUMPAD2))
    {
        M::Graphics::GraphicsSystem::Get()->SetClearColors(M::Colors::Green );
    }
}