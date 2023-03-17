#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightTypes.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include  "RenderTarget.h"

namespace M::Graphics
{
    class RenderObject;

    class ShadowEffect
    {
    public:
        void Initialize();
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetDirectionalLight(const DirectionalLight& directionalLight);

        void SetFocus(const MMath::Vector3& focusPosition) { mFocusPosition = focusPosition; }
        void SetSize(float size) { mSize = size; }

        const Camera& GetLightCamera() const { return mLightCamera; }
        const Texture& GetDepthMap() const { return mDepthRenderTarget; }

        void DebugUI();
    private:
        void UpdateLightCamera();

        struct TransformData
        {
            MMath::Matrix4 wvp;
        };
        using TransformBuffer = TypeConstantBuffer<TransformData>;

        TransformBuffer mTransformBuffer;
        VertexShader mVertexShader;
        PixelShader mPixelShader;

        const DirectionalLight* mDirectionalLight = nullptr;

        Camera mLightCamera;
        RenderTarget mDepthRenderTarget;

        MMath::Vector3 mFocusPosition;
        float mSize;
    };


}