#include "glfw_window.h"
#include <GLFW/glfw3.h>
#include "app.h"

extern DE::input_t * input_data;

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

	glfwSetKeyCallback(mWindow,DE::key_clb);
	glfwSetMouseButtonCallback(mWindow, DE::mkey_clb);
    // glfwSetCursorPosCallback(window, mpos_clb);
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

void DE::key_clb(GLFWwindow * w, int key, int scancode, int action, int modes)
{
    if(action == GLFW_PRESS)
    {
        input_data->keys[key] = key;
    }else if(action == GLFW_RELEASE)
    {
        input_data->keys[key] = 0;
    }
}

void DE::mkey_clb(GLFWwindow * w, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        input_data->keys[button] = button;
    }else if(action == GLFW_RELEASE)
    {
        input_data->keys[button] = 0;
    }
}

void DE::resize_clb(GLFWwindow*win, int w, int h)
{
	glViewport(0,0,w,h);
}
