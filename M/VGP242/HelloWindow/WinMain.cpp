#include "Core/Inc/Core.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    M::Core::Window newWindow;
    newWindow.Initialize(instance, L"Hello Window", 1920, 1080);

    while (true)
    {
        newWindow.ProcessMesage();
        if (!newWindow.IsActive())
        {
            break;
        }
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }

    newWindow.Terminate();

    return 0;
}