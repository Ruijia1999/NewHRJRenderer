#pragma once
#include "Math/Math.h"
#include "Light.h"
#include <Windows.h>
namespace HRJRenderer {
	namespace Shader {
		namespace FlatShading
		{
			Vector4 vertexShader(const HRJRenderer::Vector3& i_vec);
			void fragmentShader(const HRJRenderer::Vector3& i_vec, COLORREF& i_color, HRJRenderer::Vector3 normal, const Light::LightSetting& lightsetting);
		};
	}
	

}

