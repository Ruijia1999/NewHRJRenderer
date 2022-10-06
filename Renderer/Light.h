#pragma once
#include "Math/Math.h"
#include "Color.h"
#include <Windows.h>
namespace HRJRenderer {
	namespace Light {
		
		struct AmbientLight {

		};

		struct DiffuseLight {
			HRJRenderer::Vector3 direction;
			Color lightColor;
		};
		class LightSetting {
		public:
			DiffuseLight diffuseLight;
		};
		
	}
}