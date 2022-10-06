#include "Color.h"

HRJRenderer::Color HRJRenderer::GetColorInterpolation(HRJRenderer::Color i_color0, HRJRenderer::Color i_color1, HRJRenderer::Color i_color2, const HRJRenderer::Vector3& barycentric) {
	HRJRenderer::Color outcome = i_color0 * barycentric.x + i_color1 * barycentric.y + i_color2 * barycentric.z;
	return outcome;
}
HRJRenderer::Color HRJRenderer::Color::operator+(const Color& i_color) const {
	Color outcome = HRJRenderer::Color(R + i_color.R, G + i_color.G, B + i_color.B, A);

	return outcome;
}
HRJRenderer::Color::Color(float i_r, float i_g, float i_b, float i_a) {
	R = i_r;
	G = i_g;
	B = i_b;
	A = i_a;
}
HRJRenderer::Color::Color() {
	R = 1;
	G = 1;
	B = 1;
	A = 1;
}
COLORREF HRJRenderer::Color::ToCOLORREF() {

	return  (int)(B * 255) << 16 | (int)(G * 255) << 8 | (int)(R * 255);
}
HRJRenderer::Color HRJRenderer::Color::operator*(const HRJRenderer::Color& i_color) const {
	Color outcome = HRJRenderer::Color(R * i_color.R, G * i_color.G, B * i_color.B, A);
	
	return outcome;
}

HRJRenderer::Color HRJRenderer::Color::operator*(const float& intensity) {
	Color outcome = HRJRenderer::Color(R * intensity, G * intensity, B * intensity, A);
	return outcome;
}