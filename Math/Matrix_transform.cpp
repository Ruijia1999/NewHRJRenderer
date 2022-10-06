#include "Matrix_transform.h"
HRJRenderer::Math::Matrix_transform::Matrix_transform(const Matrix_transform& i_matrix4) {
	for (int i = 0; i < 4; i++) {
		matrix[i] = i_matrix4.matrix[i];
	}
}
HRJRenderer::Math::Matrix_transform::Matrix_transform() {
	Vector4 vec4_0(1, 0, 0, 0);
	Vector4 vec4_1(0, 1, 0, 0);
	Vector4 vec4_2(0, 0, 1, 0);
	Vector4 vec4_3(0, 0, 0, 1);

	matrix[0] = vec4_0;
	matrix[1] = vec4_1;
	matrix[2] = vec4_2;
	matrix[3] = vec4_3;
}
HRJRenderer::Math::Matrix_transform::Matrix_transform(
	const float i_00, const float i_01, const float i_02, const float i_03,
	const float i_10, const float i_11, const float i_12, const float i_13,
	const float i_20, const float i_21, const float i_22, const float i_23,
	const float i_30, const float i_31, const float i_32, const float i_33) {

	Vector4 vec4_0(i_00, i_01, i_02, i_03);
	Vector4 vec4_1(i_10, i_11, i_12, i_13);
	Vector4 vec4_2(i_20, i_21, i_22, i_23);
	Vector4 vec4_3(i_30, i_31, i_32, i_33);

	matrix[0] = vec4_0;
	matrix[1] = vec4_1;
	matrix[2] = vec4_2;
	matrix[3] = vec4_3;
}

HRJRenderer::Math::Matrix_transform::Matrix_transform(const Quaternion& i_rotation, const Vector3& i_translation)
{
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[0][3] = i_translation.x;
	matrix[1][3] = i_translation.y;
	matrix[2][3] = i_translation.z;
	matrix[3][3] = 1;

	const auto _2x = i_rotation.x + i_rotation.x;
	const auto _2y = i_rotation.y + i_rotation.y;
	const auto _2z = i_rotation.z + i_rotation.z;
	const auto _2xx = i_rotation.x * _2x;
	const auto _2xy = _2x * i_rotation.y;
	const auto _2xz = _2x * i_rotation.z;
	const auto _2xw = _2x * i_rotation.w;
	const auto _2yy = _2y * i_rotation.y;
	const auto _2yz = _2y * i_rotation.z;
	const auto _2yw = _2y * i_rotation.w;
	const auto _2zz = _2z * i_rotation.z;
	const auto _2zw = _2z * i_rotation.w;

	matrix[0][0] = 1.0f - _2yy - _2zz;
	matrix[0][1] = _2xy - _2zw;
	matrix[0][2] = _2xz + _2yw;

	matrix[1][0] = _2xy + _2zw;
	matrix[1][1] = 1.0f - _2xx - _2zz;
	matrix[1][2] = _2yz - _2xw;

	matrix[2][0] = _2xz - _2yw;
	matrix[2][1] = _2yz + _2xw;
	matrix[2][2] = 1.0f - _2xx - _2yy;
}

void HRJRenderer::Math::Matrix_transform::operator=(const Matrix_transform& i_matrix4) {
	for (int i = 0; i < 4; i++) {
		matrix[i] = i_matrix4.matrix[i];
	}
}
HRJRenderer::Vector4& HRJRenderer::Math::Matrix_transform::operator*(const Vector4& i_vec4){
	Vector4 outcome;
	int i = this->matrix[0][1];
	outcome.x = i_vec4.x * matrix[0][0] + i_vec4.y * matrix[1][0] + i_vec4.z * matrix[2][0] + i_vec4.w * matrix[3][0];
	outcome.y = i_vec4.x * matrix[0][1] + i_vec4.y * matrix[1][1] + i_vec4.z * matrix[2][1] + i_vec4.w * matrix[3][1];
	outcome.z = i_vec4.x * matrix[0][2] + i_vec4.y * matrix[1][2] + i_vec4.z * matrix[2][2] + i_vec4.w * matrix[3][2];
	outcome.w = i_vec4.x * matrix[0][3] + i_vec4.y * matrix[1][3] + i_vec4.z * matrix[2][3] + i_vec4.w * matrix[3][3];
	return outcome;
}
HRJRenderer::Vector4 HRJRenderer::Math::Matrix_transform::operator*(const Vector4& i_vec4) const {
	Vector4 outcome;
	int i = this->matrix[0][1];
	outcome.x = i_vec4.x * matrix[0][0] + i_vec4.y * matrix[1][0] + i_vec4.z * matrix[2][0] + i_vec4.w * matrix[3][0];
	outcome.y = i_vec4.x * matrix[0][1] + i_vec4.y * matrix[1][1] + i_vec4.z * matrix[2][1] + i_vec4.w * matrix[3][1];
	outcome.z = i_vec4.x * matrix[0][2] + i_vec4.y * matrix[1][2] + i_vec4.z * matrix[2][2] + i_vec4.w * matrix[3][2];
	outcome.w = i_vec4.x * matrix[0][3] + i_vec4.y * matrix[1][3] + i_vec4.z * matrix[2][3] + i_vec4.w * matrix[3][3];
	return outcome;
}

HRJRenderer::Vector4 HRJRenderer::Math::Matrix_transform::operator[](int i) const{
	return matrix[i];
}
HRJRenderer::Vector4& HRJRenderer::Math::Matrix_transform::operator[](int i){
	return matrix[i];
}