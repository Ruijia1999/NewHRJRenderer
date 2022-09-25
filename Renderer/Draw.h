#pragma once
#include "Model.h"
#include <Windows.h>
namespace HRJRenderer {
	void DrawModel(const Model& model, COLORREF i_color, HDC i_canvas);
	void DrawModelMesh(const Model& model, COLORREF i_color, HDC i_canvas);
	void DrawLine(int x0, int y0, int x1, int y1, COLORREF i_color, HDC i_canvas);
	void DrawTiangle(Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2, COLORREF i_color, HDC i_canvas);
	bool InTriangle(Vector2 i_point, Vector2 i_vtx0, Vector2 i_vtx1, Vector2 i_vtx2);
} 