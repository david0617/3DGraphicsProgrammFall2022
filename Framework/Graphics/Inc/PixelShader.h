#pragma once

namespace BobEngine::Graphics
{
	class PixelShader final
	{
	public:
		void Initialize(const std::filesystem::path& filePath, const char* entyPoint = "PS");
		void Terminate();
		void Bind();

	private:
		ID3D11PixelShader* mPixelShader = nullptr;
	};
}