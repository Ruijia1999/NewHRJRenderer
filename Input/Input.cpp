#include "Input.h"
HRJRenderer::Input::InputStatus::InputStatus() {
	isLeftPressed = false;
	isRightPressed = false;
}
HRJRenderer::Vector2 HRJRenderer::Input::InputStatus::GetDragVec(int i_x, int i_y) {
	Vector2 outcome = Vector2(i_x - initPos.x, i_y - initPos.y);
	initPos.x = i_x;
	initPos.y = i_y;
	return outcome;
}

void HRJRenderer::Input::InputStatus::StartDrag(int i_x, int i_y) {
	isLeftPressed = true;
	initPos.x = i_x;
	initPos.y = i_y;
}