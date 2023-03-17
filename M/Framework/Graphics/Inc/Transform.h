#pragma once
#include "Common.h"

namespace M::Graphics
{
	struct Transform
	{
		MMath::Vector3 position = MMath::Vector3::Zero;
		MMath::Quaternion rotation = MMath::Quaternion::Identity;
		MMath::Vector3 scale = MMath::Vector3::One;

		

		MMath::Matrix4 GetMatrix4() const
		{
			return
			{
				MMath::Matrix4::Scaling(scale) *
				MMath::Matrix4::MatrixRotationQuaternion(rotation) *
				MMath::Matrix4::Translation(position)
			};
		}
	};
}
