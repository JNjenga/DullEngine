#include "glfw_window.h"
#include <GLFW/glfw3.h>

void DE::Window::create(int width, int height)
{
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(width, height, "DEngine", NULL, NULL);

	if(!mWindow)
		glfwTerminate();

	glfwMakeContextCurrent(mWindow);
	glfwSwapInterval(1);
	should_close = false;
	auto fb_clbk = [](GLFWwindow *win, int w, int h){
		glViewport(0,0,w,h);
	};
	glfwSetFramebufferSizeCallback(mWindow, fb_clbk);
}

void DE::Window::update()
{
	if(glfwWindowShouldClose(mWindow))
		should_close = true;

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
}

void DE::Window::exit()
{
	glfwDestroyWindow(mWindow);
	glfwTerminate();
}
