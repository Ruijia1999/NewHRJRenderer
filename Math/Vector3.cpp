#include "Vector3.h"
#include <cmath>
HRJRenderer::Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

HRJRenderer::Vector3::Vector3(float i_x, float i_y, float i_z) {
	x = i_x;
	y = i_y;
	z = i_z;
}

HRJRenderer::Vector3& HRJRenderer::Vector3::operator-(const Vector3& i_vec) {
	Vector3 outcome(x-i_vec.x, y-i_vec.y, z-i_vec.z);
	return outcome;
}
float HRJRenderer::Vector3::operator*(const Vector3& i_vec) {
	return x * i_vec.x + y* i_vec.y + z* i_vec.z;
}
HRJRenderer::Vector3& HRJRenderer::Vector3::operator^(const Vector3& i_vec) {
	float h = y * i_vec.z - z * i_vec.y; 
	float m = z * i_vec.x - x * i_vec.z;
	float n = x * i_vec.y - y * i_vec.x;
	Vector3 outcome(h,m,n);
	return outcome;
}
 float& HRJRenderer::Vector3::operator[](int i) {
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	return x;
}

