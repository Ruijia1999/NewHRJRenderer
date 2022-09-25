#include "Vector3.h"
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

HRJRenderer::Vector3 HRJRenderer::Vector3::Normalize() {
	return *this;
}