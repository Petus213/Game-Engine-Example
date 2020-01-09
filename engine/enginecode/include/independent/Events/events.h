/*! \file events.h
*\brief Here all of the events are initialised.
*Without this, events would not take place.
*/

#pragma once

#include <functional>

namespace Engine {

	/*! \class EventType
	*\brief These are the possible events which could occur, including mouse and keyboard.
	*/
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

	/*! \class Event
	*\breif The event class will handle the events given to the system.
	*/
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
	/*! \class EventDispatcher
	*\brief The event dispatcher will return what type of event has been given.
	*/
	class EventDispatcher
	{
		template<typename T>
		using EventFunc = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_event(event) {}

		template<typename T>
		bool dispatch(EventFunc<T> func)
		{
			if (m_event.getEventType() == T::getStaticType())
			{
				m_event.handle(func(*((T*)&m_event)));
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};



}