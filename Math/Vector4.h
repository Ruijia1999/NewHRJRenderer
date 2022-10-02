#pragma once
#include "Vector3.h"
namespace HRJRenderer {
	class Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Vector4();
		Vector4(float i_x, float i_y, float i_z, float i_w);
		Vector4(Vector3 i_vec3, float i_w);
		void operator=(const Vector4& i_vec4);
		Vector4& operator/(const float& i);
		void operator/=(const float& i);
		float& operator[](int i);
		float operator[](int i) const;
	};
}

