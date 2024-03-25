#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace BobEngine::Graphics
{
    class RenderObject;
    class Texture;

    class PostProcessingEffect
    {
    public:
        enum class Mode
        {
            None,
            Monochrome,
            Invert,
            Mirror,
            Blur,
            Combine2,
            MotionBlur,
            ChromaticAberration,
            LensDistortion
        };

        void Initialize(const std::filesystem::path& filePath);
        void Terminate();

        void Begin();
        void End();

        void Render(const RenderObject& renderObject);

        void SetTexture(const Texture* texture, uint32_t slot = 0);
        void SetMode(Mode mode);

        void DebugUI();

    private:
        struct PostProcessData
        {
            int mode = 0;
            float params0 = 0.0f;
            float params1 = 0.0f;
            float params2 = 0.0f;
            float screenWidth;
            float screenHeight;
            float intensity;
            float padding = 0.0f;
        };
        using PostProcessBuffer = TypedConstantBuffer<PostProcessData>;
        using ColouBuffer = TypedConstantBuffer<PostProcessData>;
        PostProcessBuffer mPostProcessBuffer;

        VertexShader mVertexShader;
        PixelShader mPixelShader;
        Sampler mSampler;
        std::array <const Texture*, 4> mTexture;

        Mode mMode = Mode::None;

        float mMirrorScaleX = -1.0f;
        float mMirrorScaleY = -1.0f;
        float mBlurStrength = 5.0f;
        float mBlurConstant = 0.12f;
        float mAberrationValue = 0.005f;
        float mIntensity = 1.0f;
    };
}