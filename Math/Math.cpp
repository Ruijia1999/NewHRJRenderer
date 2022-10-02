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

HRJRenderer::Vector3 HRJRenderer::Math::GetTriangleNormal(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2) {
	auto vec0 = vtx0 - vtx1;
	auto vec1 = vtx0 - vtx2;
	Vector3 cross = vec0 ^ vec1;
	return Normalize(cross);
}
float HRJRenderer::Math::GetAngel(Vector3 vec0, Vector3 vec1){

	return (vec0*vec1)/(GetMo(vec0)*GetMo(vec1));
}

float HRJRenderer::Math::GetMo(Vector3 vec) {
	float sum = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;

	return sqrtf(sum);
}
HRJRenderer::Vector3 HRJRenderer::Math::Normalize(const HRJRenderer::Vector3& i_vec) {
	float ratio = sqrtf(i_vec.x * i_vec.x + i_vec.y * i_vec.y + i_vec.z * i_vec.z);
	return Vector3(i_vec.x / ratio, i_vec.y / ratio, i_vec.z / ratio);
}

HRJRenderer::Vector3 HRJRenderer::Math::GetBarycentric(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2, Vector2 vtx) {
	float b = ((vtx.y - vtx0.y) * (vtx2.x - vtx0.x) - (vtx.x - vtx0.x) * (vtx2.y - vtx0.y)) /
		((vtx1.y - vtx0.y) * (vtx2.x - vtx0.x) - (vtx1.x - vtx0.x) * (vtx2.y - vtx0.y));
	float c = ((vtx.y - vtx0.y) * (vtx1.x - vtx0.x) - (vtx.x - vtx0.x) * (vtx1.y - vtx0.y)) /
		((vtx2.y - vtx0.y) * (vtx1.x - vtx0.x) - (vtx2.x - vtx0.x) * (vtx1.y - vtx0.y));
	float a = 1 - b - c;
	return Vector3(a, b, c);
}
float HRJRenderer::Math::GetZBuffer(Vector3 vtx0, Vector3 vtx1, Vector3 vtx2, Vector3 barycentric) {
	return vtx0.z * barycentric.x + vtx1.z * barycentric.y + vtx2.z * barycentric.z;
}