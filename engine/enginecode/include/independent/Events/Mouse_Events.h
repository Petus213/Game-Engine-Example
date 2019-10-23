#pragma once
#include "Events/events.h"

namespace Engine {

	class MouseButtonPressedEvent : public Event
	{
	private:
		int i_MouseButton;
	public:
		MouseButtonPressedEvent();

		virtual EventType getEventType() const override { return EventType::MouseButtonPressed; }
		virtual int getCategoryFlags() const override { return EventCategoryMouseButton; }

		inline int getMouseButton() const { return i_MouseButton; }
	};

	class MouseButtonReleasedEvent : public Event
	{
	private:
		int i_MouseButton;
	public:
		MouseButtonReleasedEvent();

		virtual EventType getEventType() const override { return EventType::MouseButtonReleased; }
		virtual int getCategoryFlags() const override { return EventCategoryMouseButton; }

		inline int getMouseButton() const { return i_MouseButton; }
	};

	class MouseMovedEvent : public Event
	{
	private:
		float f_Xoffset;
		float f_Yoffset;

	public:
		MouseMovedEvent();

		virtual EventType getEventType() const override { return EventType::MouseMoved; }
		virtual int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getMouseXoffset() const { return f_Xoffset; }
		inline int getMouseYoffset() const { return f_Yoffset; }
	};

	class MouseScrolledEvent : public Event
	{
	private:
		float f_Xoffset;
		float f_Yoffset;
	public:
		MouseScrolledEvent();

		virtual EventType getEventType() const override { return EventType::MouseScrolled; }
		virtual int getCategoryFlags() const override { return EventCategoryMouse; }

		inline int getMouseXoffset() const { return f_Xoffset; }
		inline int getMouseYoffset() const { return f_Yoffset; }
	};
}