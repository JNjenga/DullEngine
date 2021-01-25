#include "IntroScene.h"
#include <engine.h>
#include <app.h>

using namespace DE;

IntroScene::IntroScene(){}

void IntroScene::onStart() 
{
	isActive = true;

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
}

void IntroScene::onUpdate(float dt) 
{
	if(App::input_data->keys[GLFW_KEY_N] == GLFW_KEY_N)
	{
			isActive = false;
	}

}

void IntroScene::onRender() 
{
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

}

void IntroScene::onDestroy() 
{

}
