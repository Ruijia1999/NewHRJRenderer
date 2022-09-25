#include "Draw.h"

void HRJRenderer::DrawModel(const Model& model, COLORREF i_color, HDC i_canvas) {
	std::vector<Vector3> face = model.m_facet_vrt;
	int faceCount = face.size();
	for (int i = 0; i < faceCount; i++) {
		Vector2 vtx0((model.m_verts[face[i][0] - 1].x + 1) * 250, (-model.m_verts[face[i][0] - 1].y + 1) * 250);
		Vector2 vtx1((model.m_verts[face[i][1] - 1].x + 1) * 250, (-model.m_verts[face[i][1] - 1].y + 1) * 250);
		Vector2 vtx2((model.m_verts[face[i][2] - 1].x + 1) * 250, (-model.m_verts[face[i][2] - 1].y + 1) * 250);
		HRJRenderer::DrawTiangle(vtx0, vtx1, vtx2, i_color, i_canvas);
	}
}
void HRJRenderer::DrawModelMesh(const Model& model, COLORREF i_color, HDC i_canvas) {
	std::vector<Vector3> face = model.m_facet_vrt;
	int faceCount = face.size();
	for (int i = 0; i < faceCount; i++) {
		for (int j = 0; j < 3; j++) {
			Vector3 v0 = model.m_verts[face[i][j]-1];
			Vector3 v1 = model.m_verts[face[i][(j + 1) % 3]-1];
			HRJRenderer::DrawLine((v0.x+1)*250, (-v0.y+1)*250, (v1.x+1)*250, (-v1.y+1)*250, i_color, i_canvas);
		}
	}
	    
}
void HRJRenderer::DrawLine(int x0, int y0, int x1, int y1, COLORREF i_color, HDC i_canvas){

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

void HRJRenderer::DrawTiangle(Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2, COLORREF i_color, HDC i_canvas) {

	//Get the rectangle
	int x_min = min(i_vtx0.x, i_vtx1.x);
	x_min = min(x_min, i_vtx2.x);
	int x_max = max(i_vtx0.x, i_vtx1.x);
	x_max = max(x_max, i_vtx2.x);
	int y_min = min(i_vtx0.y, i_vtx1.y);
	y_min = min(y_min, i_vtx2.y);
	int y_max = max(i_vtx0.y, i_vtx1.y);
	y_max = max(y_max, i_vtx2.y);


	for (int i = x_min; i <= x_max; i++ ) {
		for (int j = y_min; j <= y_max; j++) {
			//SetPixel(i_canvas, i, j, i_color);
			//Whether the point is in/on the triangle
			if (InTriangle(Vector2(i, j), i_vtx0, i_vtx1, i_vtx2)) {
				SetPixel(i_canvas, i, j, i_color);
			}
		}
	}

}

bool HRJRenderer::InTriangle(Vector2 i_point, Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2) {
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