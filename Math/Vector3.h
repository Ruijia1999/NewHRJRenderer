#pragma once
namespace HRJRenderer {
	class Vector3
	{
	public:
		float x;
		float y;
		float z;
		Vector3();
		Vector3(float i_x, float i_y, float i_z);

		float& operator[](int i);
		Vector3 Normalize();
	};
}
