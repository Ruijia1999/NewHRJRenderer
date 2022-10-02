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
		Vector3& operator-(const Vector3& i_vec);
		Vector3& operator^(const Vector3& i_vec);
		float operator*(const Vector3& i_vec);
		float& operator[](int i);
	};
}
