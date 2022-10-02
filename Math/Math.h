#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix_transform.h"
#include <cmath>

namespace HRJRenderer {
	namespace Math {
		HRJRenderer::Math::Matrix_transform CreateCameraToProjectedTransform_perspective(
			const float i_verticalFieldOfView_inRadians,
			const float i_aspectRatio,
			const float i_z_nearPlane, const float i_z_farPlane);
		Matrix_transform CreateWorldToCameraTransform(const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition);
		Matrix_transform CreateWorldToCameraTransform(Matrix_transform i_transform_localCameraToWorld);
		Vector3 GetTriangleNormal(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2);
		float GetAngel(Vector3 vec0, Vector3 vec1);
		float GetMo(Vector3 vec);
		Vector3 Normalize(const Vector3& i_vec);
		Vector3 GetBarycentric(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2, Vector2 vtx);
		float GetZBuffer(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2, Vector3 barycentric);

	}
}
