#include "Draw.h"
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