/*! \file Mouse_Events.h
*\brief This file contains all of the mouse events
*/
#pragma once
#include "Events/events.h"

namespace Engine {

	/*! \class MouseEvent
	*\breif The mouse event class will return what type of mouse button has been pressed.
	*/
	class MouseEvent : public Event {
	protected:
		int m_button;
		MouseEvent(int button) : m_button(button) {}
	public:
		virtual int getCategoryFlags() const override { return EventCategoryMouseButton | EventCategoryInput; }
		
		inline int getKeycode() const { return m_button; }
	};
	/*! \class MouseButtonPressedEvent
	*\breif The mouse button pressed event class will return when a mouse button has been pressed.
	*/
	class MouseButtonPressedEvent : public MouseEvent
	{
	private:
		int m_repeatCount;
	public:
		MouseButtonPressedEvent(int button) : MouseEvent(button){}

		virtual EventType getEventType() const override { return EventType::MouseButtonPressed; }
		static EventType getStaticType() { return EventType::MouseButtonPressed; }

		inline int getMouseButton() const { return m_repeatCount; }
	};
	/*! \class MouseButtonReleasedEvent
	*\breif The mouse button released event class will return when a mouse button has been released.
	*/
	class MouseButtonReleasedEvent : public MouseEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseEvent(button){}

		virtual EventType getEventType() const override { return EventType::MouseButtonReleased; }
		static EventType getStaticType() { return EventType::MouseButtonReleased; }

		inline int getMouseButton() const { return m_button; }
	};
	/*! \class MouseMovedEvent
	*\breif The mouse moved event class will return a value for when the mouse cursor has been moved.
	* particularly useful for first person games or other camera controls, for example.
	*/
	class MouseMovedEvent : public Event
	{
	private:
		float m_XOffset;
		float m_YOffset;

	public:
		MouseMovedEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual EventType getEventType() const override { return EventType::MouseMoved; }
		virtual int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

		static EventType getStaticType() { return EventType::MouseMoved; }

		inline int getMouseXoffset() const { return m_XOffset; }
		inline int getMouseYoffset() const { return m_YOffset; }
	};
	/*! \class MouseScrolledEvent
	*\breif The mouse scrolled event class will return when the mouse wheel has been scrolled.
	* a good use for this would be to zoom the camera in and out.
	*/
	class MouseScrolledEvent : public Event
	{
	private:
		float m_XOffset;
		float m_YOffset;
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual EventType getEventType() const override { return EventType::MouseScrolled; }
		virtual int getCategoryFlags() const override { return EventCategoryMouse; }

		static EventType getStaticType() { return EventType::MouseScrolled; }

		inline int getMouseXoffset() const { return m_XOffset; }
		inline int getMouseYoffset() const { return m_YOffset; }
	};
}