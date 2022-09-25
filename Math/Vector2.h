#pragma once
namespace HRJRenderer {
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2();
		Vector2(float i_x, float i_y);

		float& operator[](int i);
	};
}

