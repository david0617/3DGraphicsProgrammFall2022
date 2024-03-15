#pragma once

#include "ConstantBuffer.h"
#include "LightType.h"
#include "Material.h"
#include "PixelShader.h"
#include "Sampler.h"
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
        
        struct SettingsData
        {
            int useDiffuseMap = 1;
            int useNormalMap = 1;
            int useSpecMap = 1;
            int useBumpMap = 1;
            float bumpWeight = 1.0f;
            float padding[3];
        };

        using TransformBuffer = TypedConstantBuffer<Transformdata>;
        using LightBuffer = TypedConstantBuffer<DirectionalLight>;
        using MaterialBuffer = TypedConstantBuffer<Meaterial>;
        using SettingBuffer = TypedConstantBuffer<SettingsData>;

        TransformBuffer mTransformBuffer;
        LightBuffer mLightBuffer;
        MaterialBuffer mMaterialBuffer;
        SettingBuffer mSettingsBuffer;
        Sampler mSampler;
        VertexShader mVertexShader;
        PixelShader mPixelShader;

        SettingsData mSettingsData;
        const Camera* mCamera = nullptr;
        const DirectionalLight* mDirectionalLight = nullptr;
    };
}
