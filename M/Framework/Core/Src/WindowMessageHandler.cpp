#include "Precompiled.h"
#include "Core/Inc/DebugUtil.h"
#include "Core/Inc/Core.h"

using namespace M::Core;

void WindowMessageHandler::Hook(HWND window, Callback cb)
{
    mWindow = window;
    mPreviousCallback = (Callback)GetWindowLong(window, GWLP_WNDPROC);
    SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void WindowMessageHandler::UnHook()
{
    SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
    mWindow = nullptr;
}

LRESULT WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    ASSERT(mPreviousCallback, "windowMessageHandler -- No Callback is hooked.");
    return CallWindowProcA((WNDPROC)mPreviousCallback, window, message, wParam, lParam);
}