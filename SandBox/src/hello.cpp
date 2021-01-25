#include <dull_engine.h>
#include <main.h>
#include <glfw_window.h>
#include <app.h>
#include <engine.h>
#include "IntroScene.h"
#include "first_scene.h"

using namespace DE;

class Sandbox : public App 
{
	public :
		DE::Scene* scenes[2];
		int current_scene;

		Sandbox() 
		{
			width = 640;
			height = 640;
		}

		void onCreate() override 
		{
			// Initialize projection matrix
			DE::set_window_bounds(-640.0f, 640.0f, 640.0f, -640.0f);
			
			current_scene = 0;
            scenes[current_scene] = new IntroScene(); 
            scenes[current_scene]->onStart();

            scenes[1] = new FirstScene(); 
		}

		void onUpdate() override
		{
#if 0
			int key = get_key_down();
			switch(key)
			{
				case GLFW_KEY_H:
					// Do some stuff
					break;
				default:
					break;
			};
#endif

			// Option two
			if(App::input_data->keys[GLFW_KEY_ESCAPE] == GLFW_KEY_ESCAPE)
			{
				// Do some stuff
				// std::exit(1);
                isRunning = false;
			}

            if(!scenes[current_scene]->isActive)
			{
				scenes[current_scene]->onDestroy();
				if(current_scene == 1)
						current_scene = 0;
				else
						current_scene = 1;

				scenes[current_scene]->onStart();
			}

            scenes[current_scene]->onUpdate(0.0f);
		}

		void onRender() override
		{
            scenes[current_scene]->onRender();
		}

		void onExit() override
        {
            scenes[current_scene]->onDestroy();
        }
};

App * init_app()
{
	return new Sandbox();
}
