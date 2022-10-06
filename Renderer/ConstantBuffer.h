#pragma once
#include "Math/Matrix_transform.h"
#include "Model.h"
#include "Light.h"
namespace HRJRenderer {
	namespace Draw {
		struct ConstantBuffer {
		public:
			
			Math::Matrix_transform worldToCameraTransform;
			Math::Matrix_transform cameraPerspectiveTransform;
			Math::Matrix_transform localToWroldTransform;
			Light::LightSetting lightSetting;
			std::vector<Vector3> m_verts;     // array of vertices
			std::vector<Vector2> m_uv;        // array of tex coords
			std::vector<Vector3> m_norms;     // array of normal vectors
			std::vector<Vector3> m_facet_vrt;
			std::vector<Vector3> m_facet_tex;  // indices in the above arrays per triangle
			std::vector<Vector3> m_facet_nrm;
		};
	}
}