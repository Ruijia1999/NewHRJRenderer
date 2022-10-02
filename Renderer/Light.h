#pragma once
#include "Math/Math.h"
#include <Windows.h>
namespace HRJRenderer {
	namespace Light {
		
		struct AmbientLight {

		};

		struct DiffuseLight {
			HRJRenderer::Vector3 direction;
			COLORREF lightColor;
		};
		class LightSetting {
		public:
			DiffuseLight diffuseLight;
		};
		
	}
}