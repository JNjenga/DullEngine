#pragma once
#include "dull_engine.h"
#include <GLFW/glfw3.h>

namespace DE
{
	class DE_API Window
	{
		public:
			GLFWwindow * mWindow;
			bool should_close;

			void create(int width, int height);
			void update();
			void exit();
	};
}
