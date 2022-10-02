#include "Vector2.h"

HRJRenderer::Vector2::Vector2() {
	x = 0;
	y = 0;
}

HRJRenderer::Vector2::Vector2(Vector3 i_vec) {
	x = i_vec.x;
	y = i_vec.y;
}

HRJRenderer::Vector2::Vector2(float i_x, float i_y) {
	x = i_x;
	y = i_y;
}
float HRJRenderer::Vector2::operator^(const Vector2& i_vec) {
	return x * i_vec.y - i_vec.x * y;
}
HRJRenderer::Vector2& HRJRenderer::Vector2::operator/(const float& i){
	Vector2 outcome(x / i, y / i);
	return outcome;
}
HRJRenderer::Vector2& HRJRenderer::Vector2::operator-(const Vector2& i_vec) {
	Vector2 outcome(x - i_vec.x, y - i_vec.y);
	return outcome;
}
float& HRJRenderer::Vector2::operator[](int i) {
	switch (i)
	{
	case 0:
		return x;
	case 1:
		return y;
	}
}