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

	void key_clb(GLFWwindow * w, int key, int scancode, int action, int modes);
	void mkey_clb(GLFWwindow * w, int button, int action, int mods);	
	void resize_clb(GLFWwindow*win, int w, int h);
}
