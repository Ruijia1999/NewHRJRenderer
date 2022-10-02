#pragma once
#include "Math/Math.h"
namespace HRJRenderer {
	namespace Input {
		class InputStatus
		{
		public:
			bool isLeftPressed;
			bool isRightPressed;
			HRJRenderer::Vector2 GetDragVec(int i_x, int i_y);
			InputStatus();
			void StartDrag(int i_x, int i_y);
		private:
			HRJRenderer::Vector2 initPos;
		};
	}
}

