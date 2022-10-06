#pragma once
#include "Shader.h"
#include "Color.h"
namespace HRJRenderer {
	class PhongShader : IShader
	{
	public:
		Color colors[3];
		Vector3 vertexShader(const HRJRenderer::Vector3& i_vec, const HRJRenderer::Vector3& i_normal, int index, const Color& i_color, const Draw::ConstantBuffer& constantBuffer);
		COLORREF fragmentShader(const HRJRenderer::Vector3& barycentric, const Draw::ConstantBuffer& constantBuffer);
	};
}


