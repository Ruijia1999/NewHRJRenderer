#pragma once
#include "Model.h"
#include "Math/Matrix_transform.h"
#include <Windows.h>
namespace HRJRenderer {
	namespace Draw {
		struct ConstantBuffer {
		public:
			Math::Matrix_transform worldToCameraTransform;
			Math::Matrix_transform cameraPerspectiveTransform;
			Math::Matrix_transform localToWroldTransform;
		};
		void DrawModel(const Model& model, COLORREF i_color, HDC i_canvas);
		void DrawModelMesh(const Model& model, COLORREF i_color, HDC i_canvas);
		void DrawLine(const HRJRenderer::Vector2& i_vec0, const HRJRenderer::Vector2& i_vec1, COLORREF i_color, HDC i_canvas);
		void DrawTiangle(Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2, COLORREF i_color, HDC i_canvas);
		bool InTriangle(Vector2 i_point, Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2);
		Vector2 GetTriangleVtx(const Vector3& i_vec);
		void SubmitCamera(Math::Matrix_transform worldToCamera, Math::Matrix_transform project, Math::Matrix_transform localToWroldTransform);
	}
	
} 