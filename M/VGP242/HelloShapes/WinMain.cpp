#include <M/Inc/M.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Triangle,
    Square,
    Diamond
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    AppConfig config;
    config.appName = L"Hello Shapes";
    config.winWidth = 1200;
    config.winHeigth = 720;

    M::App& mainApp = M::MainApp();

    mainApp.AddState<GameState>((size_t)States::GameState);
    mainApp.AddState<Triangle>((size_t)States::Triangle);
    mainApp.AddState<Square>((size_t)States::Square);
    mainApp.AddState<Diamond>((size_t)States::Diamond);
    mainApp.Run(config);

    return 0;
}