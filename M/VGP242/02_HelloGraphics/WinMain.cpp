#include <M/Inc/M.h>
#include "GameState.h"

enum class states : size_t
{
    GameState = 0
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    M::App& mainApp = M::MainApp();

    mainApp.AddState<GameState>((size_t)states::GameState);
    mainApp.Run();

    return 0;
}