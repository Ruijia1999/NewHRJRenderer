#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
namespace HRJRenderer {
	namespace Math {
		class Matrix_transform
		{
		public:
	
			Vector4 matrix[4];
			Matrix_transform();
			Matrix_transform(const Matrix_transform& i_matrix4);
			Matrix_transform(
				const float i_00, const float i_01, const float i_02, const float i_03,
				const float i_10, const float i_11, const float i_12, const float i_13,
				const float i_20, const float i_21, const float i_22, const float i_23,
				const float i_30, const float i_31, const float i_32, const float i_33 );
			Matrix_transform(const Quaternion& i_rotation, const Vector3& i_translation);
			Vector4& operator*(const Vector4& i_matrix4);
			Vector4 operator*(const Vector4& i_matrix4) const;
			Vector4& operator[](int i);
			Vector4 operator[](int i) const;
			void operator=(const Matrix_transform& i_matrix4);
		};

	}
}

