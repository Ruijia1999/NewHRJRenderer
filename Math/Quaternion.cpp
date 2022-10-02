#include "Quaternion.h"

HRJRenderer::Math::Quaternion::Quaternion() {
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}
HRJRenderer::Math::Quaternion::Quaternion(float i_x, float i_y, float i_z, float i_w) {
	x = i_x;
	y = i_y;
	z = i_z;
	w = i_w;
}
float& HRJRenderer::Math::Quaternion::operator[](int i) {
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	return w;
}
void HRJRenderer::Math::Quaternion::operator=(const Quaternion& i_vec4) {
	x = i_vec4.x;
	y = i_vec4.y;
	z = i_vec4.z;
	w = i_vec4.w;
}