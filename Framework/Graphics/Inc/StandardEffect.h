#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "LightType.h"
#include "VertexShader.h"

namespace BobEngine::Graphics
{
    class Camera;
    class RenderObject;
    class Texture;

    class StandardEffect
    {
    public:
        void Initialize(const std::filesystem::path& filepath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetCamera(const Camera& camera);
        void setDirectionalLight(const DirectionalLight& directionalLight);

        void DebugUI();

    private:
        struct Transformdata
        {
            Math::Matrix4 wvp;
            Math::Matrix4 world;
            Math::Vector3 viewPosition;
            float padding = 0.0f;
        };
        
        using TransformBuffer = TypedConstantBuffer<Transformdata>;
        using LightBuffer = TypedConstantBuffer<DirectionalLight>;

        TransformBuffer mTransformBuffer;
        LightBuffer mLightBuffer;
        Sampler mSampler;
        VertexShader mVertexShader;
        PixelShader mPixelShader;

        const Camera* mCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
    };
}
