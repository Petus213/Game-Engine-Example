/*! \file GLFW_Context.h
* This file contains the class for Graphics context in relation to OpenGL
*/
#pragma once
#include "windows\graphicsContext.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "systems\log.h"

namespace Engine {
	/*! \class OpenGL_GLFWGraphicsContext
	* This class inherits from the class Graphics Context
	* It is specifically for OpenGL
	*/
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

