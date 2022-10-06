#pragma once
#include "Model.h"
#include "Math/Matrix_transform.h"
#include "ConstantBuffer.h"
#include "Light.h"
#include "GouraudShader.h"
#include "FlatShader.h"
#include "Shader.h"
#include <Windows.h>
namespace HRJRenderer {
	namespace Draw {
		void Initialize(int length, int width);
		void ClearColor(int height, int width);
		void DrawModel(Color i_color, int i_shaderType, HDC i_canvas);
		void DrawModelMesh(const Model& model, Color i_color, HDC i_canvas);
		void DrawLine(const HRJRenderer::Vector2& i_vec0, const HRJRenderer::Vector2& i_vec1, Color i_color, HDC i_canvas);
		void DrawTiangleFlat(int i_face, Color i_color, HDC i_canvas);
		void DrawTiangleGouraud(int index, HDC i_canvas);
		bool InTriangle(Vector2 i_point, Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2);
		Vector3 GetTriangleVtx(const Vector3& i_vec);
		void SubmitCamera(Math::Matrix_transform worldToCamera, Math::Matrix_transform project, Math::Matrix_transform localToWroldTransform);
		void SubmitLight(const Light::LightSetting& i_lightSetting, const HRJRenderer::Model& model);
		void SubmitLight(const HRJRenderer::Light::LightSetting& i_lightSetting);
	}
	
} 