#include "engine_pch.h"
#include "windows\GLFW_Context.h"
#include "systems\log.h"


namespace Engine {

	OpenGL_GLFWGraphicsContext::OpenGL_GLFWGraphicsContext(GLFWwindow* window) : m_window(window)
	{
	}

	void OpenGL_GLFWGraphicsContext::init()
	{
		glfwMakeContextCurrent(m_window);
		int result = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		NG_ASSERT(result, "Failed To initialise GLAD");
	}

	void OpenGL_GLFWGraphicsContext::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

}