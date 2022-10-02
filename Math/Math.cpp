#include "Math.h"
HRJRenderer::Math::Matrix_transform HRJRenderer::Math::CreateWorldToCameraTransform(
	const Quaternion& i_cameraOrientation, const Vector3& i_cameraPosition)
{
	return CreateWorldToCameraTransform(Matrix_transform(i_cameraOrientation, i_cameraPosition));
}

HRJRenderer::Math::Matrix_transform HRJRenderer::Math::CreateWorldToCameraTransform(HRJRenderer::Math::Matrix_transform i_transform_localCameraToWorld)
{

	return HRJRenderer::Math::Matrix_transform(
		i_transform_localCameraToWorld.matrix[0][0], i_transform_localCameraToWorld.matrix[0][1], i_transform_localCameraToWorld.matrix[0][2], 0.0f,
		i_transform_localCameraToWorld.matrix[1][0], i_transform_localCameraToWorld.matrix[1][1], i_transform_localCameraToWorld.matrix[1][2], 0.0f,
		i_transform_localCameraToWorld.matrix[2][0], i_transform_localCameraToWorld.matrix[2][1], i_transform_localCameraToWorld.matrix[2][2], 0.0f,

		-(i_transform_localCameraToWorld.matrix[0][3] * i_transform_localCameraToWorld.matrix[0][0]) - (i_transform_localCameraToWorld.matrix[1][3] * i_transform_localCameraToWorld.matrix[1][0]) - (i_transform_localCameraToWorld.matrix[2][3] * i_transform_localCameraToWorld.matrix[2][0]),
		-(i_transform_localCameraToWorld.matrix[0][3] * i_transform_localCameraToWorld.matrix[0][1]) - (i_transform_localCameraToWorld.matrix[1][3] * i_transform_localCameraToWorld.matrix[1][1]) - (i_transform_localCameraToWorld.matrix[2][3] * i_transform_localCameraToWorld.matrix[2][1]),
		-(i_transform_localCameraToWorld.matrix[0][3] * i_transform_localCameraToWorld.matrix[0][2]) - (i_transform_localCameraToWorld.matrix[1][3] * i_transform_localCameraToWorld.matrix[1][2]) - (i_transform_localCameraToWorld.matrix[2][3] * i_transform_localCameraToWorld.matrix[2][2]),

		1.0f);
}


HRJRenderer::Math::Matrix_transform HRJRenderer::Math::CreateCameraToProjectedTransform_perspective(
	const float i_verticalFieldOfView_inRadians,
	const float i_aspectRatio,
	const float i_z_nearPlane, const float i_z_farPlane)
{
	const auto yScale = 1.0f / std::tan(i_verticalFieldOfView_inRadians * 0.5f);
	const auto xScale = yScale / i_aspectRatio;


	const auto zDistanceScale = 1.0f / (i_z_nearPlane - i_z_farPlane);
	float z = (i_z_nearPlane + i_z_farPlane) * zDistanceScale;
	return Matrix_transform(
		xScale, 0.0f, 0.0f, 0.0f,
		0.0f, yScale, 0.0f, 0.0f,
		0.0f, 0.0f, (i_z_nearPlane + i_z_farPlane) * zDistanceScale, -1.0f,
		0.0f, 0.0f, (2.0f * i_z_nearPlane * i_z_farPlane) * zDistanceScale, 0.0f);

}