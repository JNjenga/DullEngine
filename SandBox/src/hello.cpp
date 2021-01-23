#include <dull_engine.h>
#include <main.h>
#include <glfw_window.h>
#include <app.h>
#include <engine.h>

using namespace DE;

extern DE_API DE::input_t * input_data;

class Sandbox : public App 
{
	public :
		Mesh mesh;
		Sandbox() 
		{
			width = 640;
			height = 640;
		}

		void onCreate() override 
		{
			// Initialize projection matrix
			DE::set_window_bounds(-640.0f, 640.0f, 640.0f, -640.0f);

			float vertices[] = {
				-1.0f, 1.0f, 0.0f, // Top left
				1.0f, 1.0f, 0.0f, // Top right
				1.0f, -1.0f, 0.0f, // Bottom right
				-1.0f, -1.0f, 0.0f, // Bottom left
			};

			float tex_coords[] = {
				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f
			};
			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			// mesh.vao_id = create_mesh2d(vertices, 12, indices, 6);
			mesh.vao_id = create_mesh({12, 6, 8, vertices, tex_coords, indices});
			mesh.texture_id = create_texture("assets/joker.png");

			mesh.x = -540.0f;
			mesh.y = 540.0f;
			mesh.scale = 100.0f;
			mesh.vertex_count = 6;
		};

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
			if(input_data->keys[GLFW_KEY_ESCAPE] == GLFW_KEY_ESCAPE)
			{
				// Do some stuff
				// std::exit(1);
                isRunning = false;
			}
		};

		void onRender() override
		{
#if 1
			for(size_t i = 0; i < 7; i++)
			{
				for(size_t j = 0; j < 7; j++)
				{
					draw_mesh2d(&mesh);
					mesh.x += 200.0f;
				}
				mesh.x = -540.0f;
				mesh.y -= 200.0f;
			}

			mesh.y = 540.0f;
#else
			mesh.x = -640.0f;
			mesh.y = 640.0f;
			draw_mesh2d(&mesh);
#endif
		};

		void onExit() override {};
};

App * init_app()
{
	return new Sandbox();
}
