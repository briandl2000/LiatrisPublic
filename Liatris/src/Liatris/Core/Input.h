#pragma once

#include "Liatris/Core/Base.h"

namespace Liatris {
	
	class Input 
	{
	public:
		static bool IsKeyPressed(int keycode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		static float GetMouseDeltaX();
		static float GetMouseDeltaY();
	};


}