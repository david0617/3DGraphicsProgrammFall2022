#include <BobEngine/Inc/BobEngine.h>
#include "GameState.h"

using namespace BobEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	App& mainApp = BobEngine::MainApp();
	mainApp.AddState<GameState>("GameState");

	AppConfig config;
	config.appName = L"08_HelloLighting";
	config.winWidth = 1280;
	config.winHeight = 780;
	mainApp.Run(config);

	return(0);
}