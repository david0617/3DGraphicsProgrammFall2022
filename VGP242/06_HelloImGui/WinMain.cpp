#include <BobEngine/Inc/BobEngine.h>

#include "GameState.h"

using namespace BobEngine;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	AppConfig config;
	config.appName = L"Hello ImGui";

	App& myApp = MainApp();
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return(0);
}