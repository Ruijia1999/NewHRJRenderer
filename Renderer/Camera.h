#pragma once
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
namespace HRJRenderer {
	class Camera
	{
	public:
		Vector3 position;
		Math::Quaternion rotate;
		float verticalFieldOfView_inRadians;
		float nearPlane;
		float farPlane;
		float aspectRatio;
		void Move(Vector3 i_vec);
	};
}


