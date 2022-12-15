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

    return sWindowMessageHandler.ForwardMessage(handle, message, wparam, lparam);
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

    //sWindowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
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
    mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
    mImmediateContext->ClearRenderTargetView(mRenderTargetView, (FLOAT*)(&mClearClolr));
    mImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void GraphicsSystem::ENdRender()
{
    mSwapChain->Present(mVSync, 0);
}

void GraphicsSystem::ToggleFullscreen()
{
    BOOL fullScreen;
    mSwapChain->GetFullscreenState(&fullScreen, nullptr);
    mSwapChain->SetFullscreenState(!fullScreen, nullptr);
}

void GraphicsSystem::Resize(uint32_t width, uint32_t height)
{
    mImmediateContext->OMSetRenderTargets(0, nullptr, nullptr);

    safeRealease(mRenderTargetView);
    safeRealease(mDepthStencilView);

    HRESULT hr;
    if (width != GetBackBufferWidth() || height != GetBackBufferHeight())
    {
        hr = mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
        ASSERT(SUCCEEDED(hr), "[Error] faild to resize swap chain buffer");

        mSwapChain->GetDesc(&mSwapChainDesc);
    }

    ID3D11Texture2D* backBuffer = nullptr;
    hr = mSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    ASSERT(SUCCEEDED(hr), "[Error] failed to access swap chain view");

    hr = mD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView);
    safeRealease(backBuffer);
    ASSERT(SUCCEEDED(hr), "[Error] failed create render target view");

    //Depth stencil buffed
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = GetBackBufferWidth();
    descDepth.Height = GetBackBufferHeight();
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = mD3DDevice->CreateTexture2D(&descDepth, nullptr, &mDepthStencilBuffer);
    ASSERT(SUCCEEDED(hr), "[Error] faild create deapth stencil buffer");

    //Depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = mD3DDevice->CreateDepthStencilView(mDepthStencilBuffer, &descDSV, &mDepthStencilView);
    ASSERT(SUCCEEDED(hr), "[Error] failed create depth stencil view");

    //setup the viewport
    mViewport.Width = static_cast<float>(GetBackBufferWidth());
    mViewport.Height = static_cast<float>(GetBackBufferHeight());
    mViewport.MinDepth = 0.0f;
    mViewport.MaxDepth = 1.0f;
    mViewport.TopLeftX = 0;
    mViewport.TopLeftY = 0;
    mImmediateContext->RSSetViewports(1, &mViewport);
}

void GraphicsSystem::ResetRenderTarget()
{
    mImmediateContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}

void GraphicsSystem::ResetViewport()
{
    mImmediateContext->RSSetViewports(1, &mViewport);
}

void GraphicsSystem::SetClearColors(Color clearColor)
{
    mClearClolr = clearColor;
}

void GraphicsSystem::SetVSync(bool vSync)
{
    mVSync = vSync ? 1 : 0;
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