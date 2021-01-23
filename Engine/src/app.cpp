#include <GL/glew.h>
#include "app.h"
#include "engine.h"
#include "colors.h"
#include <stdlib.h> 

DE_API DE::input_t * input_data;

DE::App::App()
{
}

DE::App::App(const char * title, int width, int height)
{
}

DE::App::~App()
{
	delete window;
}

void DE::App::create()
{
	input_data = new DE::input_t();
	input_data->keys = new int[1024];

	window = new DE::Window();
	window->create(width, height);

	if(glewInit() != GLEW_OK)
	{
		exit();
	}

	DE::init_engine();

	{
		DE::Color white = DE::Color{1.0f, 0.0f, 1.0f, 1.0f};
		DE::clear(white);
	}

	DE::clear();
	onCreate();
}

void DE::App::update()
{
	onUpdate();
}

void DE::App::render()
{
	DE::clear();

	onRender();

	window->update();

	if(window->should_close)
		isRunning = false;
}

void DE::App::exit()
{
	onExit();
	delete input_data->keys;
	delete input_data;
}
