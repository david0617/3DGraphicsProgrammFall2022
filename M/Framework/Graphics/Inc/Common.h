#pragma once

// Engine Headers
#include <Core/Inc/Core.h>
#include <Math\Inc\MMath.h>

// DirectX Headers
#include <d3d11_1.h>
#include <d3dcompiler.h>

// External Headers


// DirectX libraries
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "dxguid.lib")

template <class T>
inline void safeRealease(T*& ptr)
{
    if (ptr)
    {
        ptr->Release();
        ptr = nullptr;
    }
}
