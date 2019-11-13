#include "engine_pch.h"

#include "windows\GLFW_Windows.h"
#include "windows\GLFW_Context.h"
#include "Events\Window_Events.h"
#include "Events\Keyboard_Events.h"
#include "Events\Mouse_Events.h"
#include "systems\log.h"
#include "windows\GLFWCodes.h"

namespace Engine {

	

	static void GLFWErrorCallback(int error, const char* description)
	{
		NG_INFO("GLFW Error {0} : {1}", error, description);
	}

	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties);
	}


	void GLFWWindowImpl::init(const WindowProperties & properties)
	{
		m_properties = properties;

		NG_INFO("Creating Window {0} ({1}, {2})", properties.m_title, properties.m_width, properties.m_height);

		m_nativeWindow = glfwCreateWindow((int)properties.m_width, (int)properties.m_height, properties.m_title.c_str(), nullptr, nullptr);
		
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

		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			callback(event);
		});

		glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			
			switch (action)
			{
				case KEY_PRESS:
				{
					KeyPressedEvent event(key, 0);
					callback(event);
					break;
				}
				case KEY_RELEASE:
				{
					KeyReleasedEvent event(key);
					callback(event);
					break;
				}
				case KEY_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_nativeWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			callback(event);
		});

		glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case KEY_PRESS:
			{
				MouseButtonPressedEvent event(button);
				callback(event);
				break;
			}
			case KEY_RELEASE:
				MouseButtonPressedEvent event(button);
				callback(event);
				break;
			}
		});

		glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			std::function<void(Event&)>& callback = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			callback(event);
		});
	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_nativeWindow);
		
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
		m_properties.m_height = height;
		m_properties.m_width = width;
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
	//WINDOWS SYSTEM//
/////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GLFWWindowSystem::m_active = false;
	void GLFWWindowSystem::start(SystemSignal init, ...)
	{
		if (!m_active)
		{
			m_active = true;
			NG_INFO("Initializing GLFW");
			int success = glfwInit();
			NG_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
		}
	}

	void GLFWWindowSystem::stop(SystemSignal close, ...)
	{
		if (m_active)
		{
			m_active = false;
			NG_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

}