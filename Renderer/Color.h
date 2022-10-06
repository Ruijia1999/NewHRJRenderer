#pragma once
#include <Windows.h>
#include "Math/Math.h"
namespace HRJRenderer {
	
	class Color
	{
	public:
		float R;
		float G;
		float B;
		float A;
		Color(float i_r, float i_g, float i_b, float a);
		Color();
		COLORREF ToCOLORREF();
		Color operator*(const Color& i_color) const;
		Color operator*(const float& intensity);
		Color operator+(const Color& i_color) const;
	};
	Color GetColorInterpolation(Color i_color0, Color i_color1, Color i_color2, const Vector3& barycentric);
}

