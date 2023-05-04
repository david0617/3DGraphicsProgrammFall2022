#include <M/Inc/M.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Cube = 1,
    Rectangle=2,
    Plane=3,
    Cylinder=4,
    Sphere=5
};

int WINAPI  WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    M::App& mainApp = M::MainApp();
    mainApp.AddState<GameState>((size_t)States::GameState);
    M::AppConfig config;
    config.appName = L"Hello Grain";
    config.winWidth = 1200;
    config.winHeigth =900;

    mainApp.Run(config);

    return 0;
}