#pragma once
#include "windows\graphicsContext.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"


namespace Engine {

	class OpenGL_GLFWGraphicsContext : public GraphicsContext
	{
	public:
		OpenGL_GLFWGraphicsContext(GLFWwindow* window);
		void init() override;
		void swapBuffers() override;
	private:
		GLFWwindow* m_window;

	};

}

