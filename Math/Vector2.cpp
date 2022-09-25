#include "Vector2.h"
HRJRenderer::Vector2::Vector2() {
	x = 0;
	y = 0;
}

HRJRenderer::Vector2::Vector2(float i_x, float i_y) {
	x = i_x;
	y = i_y;
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