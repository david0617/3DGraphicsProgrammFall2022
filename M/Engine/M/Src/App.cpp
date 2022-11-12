#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace M;
using namespace M::Core;

void App::ChangeState(size_t stateId)
{
    auto iter = mAppStates.find(stateId);
    if (iter != mAppStates.end())
    {
        mNextState = iter->second.get();
    }
}

void App::Run()
{
    Window myWindow;
    myWindow.Initialize(GetModuleHandle(nullptr), L"Hello Window", 1200, 720);

    ASSERT(mCurrentState, "App -- no app state found!");
    mCurrentState->Initialize();

    mRunning = true;
    while (mRunning)
    {
        myWindow.ProcessMesage();
        if (!myWindow.IsActive() || GetAsyncKeyState(VK_ESCAPE))
        {
            Quit();
            continue;
        }

        if (mNextState != nullptr)
        {
            mCurrentState->Terminate();
            mCurrentState = std::exchange(mNextState, nullptr);
            mCurrentState->Initialize();
        }

        auto deltaTime = TimeUtil::GetDelaTime();
        mCurrentState->Update(deltaTime);

        mCurrentState->Render();
    }

    mCurrentState->Terminate();

    myWindow.Terminate();
}

void App::Quit()
{
    mRunning = false;
}