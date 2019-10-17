#pragma once

namespace Engine {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, windowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryWindow = 1 << 0,
		EventCategoryInput = 1 << 1,
		EventCategoryKeyboard = 1 << 2,
		EventCategoryMouse = 1 << 3,
		EventCategoryMouseButton = 1 << 4,
	};

	class Event
	{
	private:
		bool m_handled = false;

	public:
		virtual EventType getEventType() const = 0;
		virtual int getCategoryFlags() const = 0;
		inline bool handled() const { return m_handled; }
		inline void handle(bool isHandled) { m_handled = isHandled; }
		inline bool isInCategory(EventCategory category) { return getCategoryFlags()& category; }
	};

}