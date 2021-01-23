#pragma once

#include "dull_engine.h"
#include "glfw_window.h"

namespace DE
{
	struct DE_API input_t
	{
		int *keys;
		float mouse_x, mouse_y;
	};

	class DE_API App
	{
		protected:
			Window *window;
		public:
			int width, height;
			bool isRunning;

			App(const char * title, int width, int height);
			App();

			virtual void onCreate() = 0;
			virtual void onRender() = 0;
			virtual void onUpdate() = 0;
			virtual void onExit() = 0;

			void create();
			void render();
			void update();
			void exit();

			virtual ~App();
	};
}
