#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace BobEngine::Graphics
{
    class Camera;
    class RenderObjectd;
    class Texture;

    class StandardEffect
    {
    public:
        void Initialize(const std::filesystem::path& filepath);
        void Terminate();

        void Begin();
        void end();

        void Render(const RenderObject& renderObject);

        void SetCamera(const Camera& camera);

        void DebugUI();

    private:
        struct Transformdata
        {
            Math::Matrix4 wvp;
        };
        
        using TransformBuffer = TypedConstantBuffer<Transformdata>;

        TransformBuffer mTransformBuffer;
        Sampler mSampler;
        VertexShader mVertexShader;
        PixelShader mPixelShader;

        const Camera* mCamera = nullptr;
    };
}
