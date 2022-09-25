#pragma once
#include "Model.h"
#include <Windows.h>
namespace HRJRenderer {
	void DrawModelMesh(const Model& model, COLORREF i_color, HDC i_canvas);
	void DrawLine(int x0, int y0, int x1, int y1, COLORREF i_color, HDC i_canvas);
} 