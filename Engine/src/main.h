#pragma once

#include "dull_engine.h"
#include "engine.h"
#include "app.h"

extern DE::App * init_app();

int main(int argc, char *argv[])
{
	DE::App * app = init_app();

	app->isRunning = true;
	app->create();

	while(app->isRunning)
	{
		app->update();
		app->render();
	}
	
	app->exit();
	delete app;

	return 0;
}
