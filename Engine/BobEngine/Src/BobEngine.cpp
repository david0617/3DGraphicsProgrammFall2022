#include "Precompiled.h"
#include "BobEngine.h"

BobEngine::App& BobEngine::MainApp()
{
	static App sApp;
	return sApp;
}
