#include "Draw.h"

HRJRenderer::Draw::ConstantBuffer s_constantBuffer;
std::vector<std::vector<float>> zBuffer;


void HRJRenderer::Draw::Initialize(int height, int width) {
	for (int i = 0; i < height; i++) {
		std::vector<float> vec;
		for (int j = 0; j < width; j++) {
			vec.push_back(FLT_MAX);
		}
		zBuffer.push_back(vec);
	}
}
void HRJRenderer::Draw::ClearColor(int height, int width) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			zBuffer[i][j] = FLT_MAX;
		}
		
	}
}
//Submit constantBuffer
void HRJRenderer::Draw::SubmitCamera(Math::Matrix_transform worldToCamera, Math::Matrix_transform project, Math::Matrix_transform localToWroldTransform) {
	s_constantBuffer.cameraPerspectiveTransform = project;
	s_constantBuffer.worldToCameraTransform = worldToCamera;
	s_constantBuffer.localToWroldTransform = localToWroldTransform;
}

void HRJRenderer::Draw::SubmitLight(const HRJRenderer::Light::LightSetting& i_lightSetting) {
	s_constantBuffer.lightSetting = i_lightSetting;
}

//Some draw functions
void HRJRenderer::Draw::DrawModel(const Model& model, COLORREF i_color, HDC i_canvas) {
	std::vector<Vector3> face = model.m_facet_vrt;
	int faceCount = face.size();
	for (int i = 0; i < faceCount; i++) {
		Vector3 normal = Math::GetTriangleNormal(model.m_verts[face[i][0] - 1], model.m_verts[face[i][1] - 1], model.m_verts[face[i][2] - 1]);
		COLORREF newColor = i_color * Math::GetAngel(normal, s_constantBuffer.lightSetting.diffuseLight.direction);
		HRJRenderer::Draw::DrawTiangle(
			GetTriangleVtx(model.m_verts[face[i][0] - 1]), 
			GetTriangleVtx(model.m_verts[face[i][1] - 1]), 
			GetTriangleVtx(model.m_verts[face[i][2] - 1]),
			newColor, i_canvas);
	}
}

void HRJRenderer::Draw::DrawModelMesh(const Model& model, COLORREF i_color, HDC i_canvas) {
	std::vector<Vector3> face = model.m_facet_vrt;
	int faceCount = face.size();
	for (int i = 0; i < faceCount; i++) {
		for (int j = 0; j < 3; j++) {
			Vector3 v0 = model.m_verts[face[i][j]-1];
			Vector3 v1 = model.m_verts[face[i][(j + 1) % 3]-1];
			HRJRenderer::Draw::DrawLine(GetTriangleVtx(v0),GetTriangleVtx(v1), i_color, i_canvas);
		}
	}
	    
}
void HRJRenderer::Draw::DrawLine(const HRJRenderer::Vector2& i_vec0, const HRJRenderer::Vector2& i_vec1, COLORREF i_color, HDC i_canvas){
	int x0 = i_vec0.x;
	int y0 = i_vec0.y;
	int x1 = i_vec1.x;
	int y1 = i_vec1.y;

	bool steep = false;

	//Avoid broken line
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	float dy = (y1 - y0) / float(x1 - x0);
	float y = y0;

	for (int x = x0; x <= x1; x++) {
		if (steep) {
			SetPixel(i_canvas, y, x, i_color);
		}
		else {
			SetPixel(i_canvas, x, y, i_color);
		}

		y += dy;

	}
	    
}
HRJRenderer::Vector3 HRJRenderer::Draw::GetTriangleVtx(const HRJRenderer::Vector3& i_vec) {
	HRJRenderer::Vector4 vtx_Camera = s_constantBuffer.worldToCameraTransform * HRJRenderer::Vector4(i_vec, 1);
	HRJRenderer::Vector4 vtx_Projected = s_constantBuffer.cameraPerspectiveTransform * (vtx_Camera);
	vtx_Projected /= vtx_Projected.w;
	HRJRenderer::Vector3 vtx_View((vtx_Projected.x + 1) * 250, (-vtx_Projected.y + 1) * 250, (vtx_Projected.z + 1) * 250);
	return vtx_View;
}
void HRJRenderer::Draw::DrawTiangle(Vector3 i_vtx0, Vector3 i_vtx1, Vector3 i_vtx2, COLORREF i_color, HDC i_canvas) {

	//Get the rectangle
	int x_min = min(i_vtx0.x, i_vtx1.x);
	x_min = min(x_min, i_vtx2.x);
	int x_max = max(i_vtx0.x, i_vtx1.x);
	x_max = max(x_max, i_vtx2.x);
	int y_min = min(i_vtx0.y, i_vtx1.y);
	y_min = min(y_min, i_vtx2.y);
	int y_max = max(i_vtx0.y, i_vtx1.y);
	y_max = max(y_max, i_vtx2.y);

	
	//Avoid drawing outside the screen;
	x_max = min(x_max, 500-1);
	x_min = max(x_min, 1);
	y_max = min(y_max, 500-1);
	y_min = max(y_min, 1);

	for (int i = x_min; i <= x_max; i++ ) {
		for (int j = y_min; j <= y_max; j++) {
			
			//Whether the point is in/on the triangle
			if (InTriangle(Vector2(i, j), i_vtx0, i_vtx1, i_vtx2)) {
				Vector3 vec = Math::GetBarycentric(i_vtx0, i_vtx1, i_vtx2, HRJRenderer::Vector2(i,j));
				float zbuffer = Math::GetZBuffer(i_vtx0, i_vtx1, i_vtx2, vec);
				if (zBuffer[i][j] > zbuffer) {
					zBuffer[i][j] = zbuffer;
					SetPixel(i_canvas, i, j, i_color);
				}
				
			}
		}
	}

}

bool HRJRenderer::Draw::InTriangle(Vector2 i_point, Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2) {
	Vector2 PA = i_vtx0 - i_point;
	Vector2 PB = i_vtx1 - i_point;
	Vector2 PC = i_vtx2 - i_point;
	float cross_0 = PA ^ PB;
	float cross_1 = PB ^ PC;
	float cross_2 = PC ^ PA;
	if (cross_0 * cross_1 >= 0 && cross_1 * cross_2 >= 0) {
		return true;
	}
	else {
		return false;
	}
}