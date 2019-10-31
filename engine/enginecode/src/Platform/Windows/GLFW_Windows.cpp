#include "windows\GLFW_Windows.h"
#include "engine_pch.h"
#include "windows\GLFW_Context.h"
#include "Events\Window_Events.h"
#include "Events\Mouse_Events.h"
#include "systems\log.h"

namespace Engine {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NG_INFO("GLFW Error {0}: {1}", error, description);
	}

	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties);
	}


	void GLFWWindowImpl::init(const WindowProperties & properties)
	{
		m_properties = properties;

		NG_INFO("Creating Window {0} ({1}, {2})", properties.m_title, properties.m_width, properties.m_height);

		if (s_GLFWWindowCount == 0)
		{
			NG_INFO("Initializing GLFW");
			int success = glfwInit();
			NG_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_nativeWindow = glfwCreateWindow((int)properties.m_width, (int)properties.m_height, properties.m_title.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;

		m_context = std::make_unique<OpenGL_GLFWGraphicsContext>(m_nativeWindow);

		m_context->init();

		glfwSetWindowUserPointer(m_nativeWindow, &m_callback);
		setVSync(true);

		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow * window)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			callback(event);
		});

	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_nativeWindow);
		if (--s_GLFWWindowCount == 0)
		{
			NG_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties & properties)
	{
		init(properties);
	}

	GLFWWindowImpl::~GLFWWindowImpl()
	{
		close();
	}

	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_context->swapBuffers();
	}

	void GLFWWindowImpl::onResize(unsigned int width, unsigned int height)
	{
	}

	void GLFWWindowImpl::setVSync(bool VSync)
	{
		if (VSync)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_properties.m_isVSync = VSync;
	}

	void GLFWWindowImpl::setEventCallback(const std::function<void(Event&)>& callback) 
	{
		m_callback = callback;
	}

}