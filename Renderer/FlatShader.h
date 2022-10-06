#pragma once
#include "Shader.h"
#include "Color.h"
namespace HRJRenderer {
	class FlatShader:IShader
	{
	public:
		Vector3 vertexShader(const HRJRenderer::Vector3& i_vec, const Draw::ConstantBuffer& constantBuffer);
		COLORREF fragmentShader(Color& i_color, HRJRenderer::Vector3 normal, const Draw::ConstantBuffer& constantBuffer);
	};

}

