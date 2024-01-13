#pragma once

namespace BobEngine::Graphics
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer() = default;
		virtual ~ConstantBuffer();

		void Initialize(uint32_t bufferSize);
		void Terminate();

		void Update(const void* data);

		void BindVS(uint32_t slot) const;
		void BindPS(uint32_t slot) const;

	private:
		ID3D11Buffer* mConstantBuffer = nullptr;
	};

	template<class DataType>
	class TypedConstantBuffer final : public ConstantBuffer
	{
	public:
		void Initialize()
		{
			static_assert(sizeof(DataType) % 16 == 0, "Data type must be 16 byte aligne");
			ConstantBuffer::Initialize(sizeof(DataType));
		}
		void UPdate(const DataType& data) const
		{
			ConstantBuffer::Update(&data);
		}
	};
}