#include "Precompiled.h"
#include "GraphicsSystem.h"

using namespace M;
using namespace M::Graphics;

namespace
{
    std::unique_ptr<GraphicsSystem> sGraphicsSystem;
    Core::WindowMessageHandler sWindowMessageHandler;
}

LRESULT CALLBACK GraphicsSystem::GraphicsSystemMessageHandler(HWND handle, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (sGraphicsSystem)
    {
        switch (message)
        {
        case WM_SIZE:
        {
            const uint32_t width = static_cast<uint32_t>(LOWORD(lparam));
            const uint32_t height = static_cast<uint32_t>(LOWORD(lparam));
            sGraphicsSystem->Resize(width, height);
            break;
        }
        }
    }
}

void GraphicsSystem::StaticInitializ(HWND window, bool fullscreen)
{
    ASSERT((sGraphicsSystem == nullptr), "");
    sGraphicsSystem = std::make_unique<GraphicsSystem>();
    sGraphicsSystem->Initialize(window, fullscreen);
}

void GraphicsSystem::StaticTerminate()
{
    if (sGraphicsSystem != nullptr)
    {
        sGraphicsSystem->Terminate();
        sGraphicsSystem.reset();
    }
}

GraphicsSystem* GraphicsSystem::Get()
{
    ASSERT((sGraphicsSystem != nullptr), "[Error] GraphicsSystem is not created");
    return sGraphicsSystem.get();
}

GraphicsSystem::~GraphicsSystem()
{
    ASSERT((mD3DDevice == nullptr), "[Error] GraphicsSystem Terminate() nust be called to cleam up");
}

void GraphicsSystem::Initialize(HWND window, bool fullscreen)
{
    RECT clientRect = {};
    GetClientRect(window, &clientRect);
    UINT width = (UINT)(clientRect.right - clientRect.left);
    UINT height = (UINT)(clientRect.bottom - clientRect.top);

    DXGI_SWAP_CHAIN_DESC swapChainDese = {};
    swapChainDese.BufferCount = 2;
    swapChainDese.BufferDesc.Width = width;
    swapChainDese.BufferDesc.Height = height;
    swapChainDese.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDese.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDese.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDese.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDese.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDese.OutputWindow = window;
    swapChainDese.SampleDesc.Count = 1;
    swapChainDese.SampleDesc.Quality = 0;
    swapChainDese.Windowed != fullscreen;
    swapChainDese.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        &featureLevel,
        1,
        D3D11_SDK_VERSION,
        &swapChainDese,
        &mSwapChain,
        &mD3DDevice,
        nullptr,
        &mImmediateContext
    );

    ASSERT(SUCCEEDED(hr), "[Error] failed to initailize device or swap chain");

    mSwapChain->GetDesc(&mSwapChainDesc);

    Resize(GetBackBufferWidth(), GetBackBufferHeight());

    sWindowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
}

void GraphicsSystem::Terminate()
{
    sWindowMessageHandler.UnHook();

    safeRealease(mDepthStencilView);
    safeRealease(mDepthStencilBuffer);
    safeRealease(mRenderTargetView);
    safeRealease(mSwapChain);
    safeRealease(mImmediateContext);
    safeRealease(mD3DDevice);
}

void GraphicsSystem::BeginRender()
{

}

void GraphicsSystem::ENdRender()
{

}

void GraphicsSystem::ToggleFullscreen()
{

}

void GraphicsSystem::Resize(uint32_t width, uint32_t height)
{

}

void GraphicsSystem::ResetRenderTarget()
{

}

void GraphicsSystem::ResetViewport()
{

}

void GraphicsSystem::SetClearColors(Color clearColor)
{

}

void GraphicsSystem::SetVSync(bool vSync)
{

}

uint32_t GraphicsSystem::GetBackBufferWidth() const
{
    return mSwapChainDesc.BufferDesc.Width;
}

uint32_t GraphicsSystem::GetBackBufferHeight() const
{
    return mSwapChainDesc.BufferDesc.Height;
}

float GraphicsSystem::GetBackBufferAspectRatio() const
{
    return static_cast<float>(GetBackBufferWidth()) / static_cast<float>(GetBackBufferHeight());
}