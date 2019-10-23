#pragma once
#include "Events/events.h"

namespace Engine {

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EventType getEventType() const override { return EventType::WindowClose; }
		int getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class WindowResizeEvent : public Event
	{
	private:
		int m_width;
		int m_height;

	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {}

		virtual EventType getEventType() const override { return EventType::WindowResize; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }

		inline int getWidth() const { return m_width; }
		inline int getHeight() const { return m_height; }
	};

	class WindowFocusEvent : public Event
	{
	private:

	public:
		WindowFocusEvent();
		virtual EventType getEventType() const override { return EventType::WindowFocus; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }

	};

	class WindowLostFocusEvent : public Event
	{
	private:
		float xPos;
		float yPos;
	public:
		WindowLostFocusEvent();
		virtual EventType getEventType() const override { return EventType::windowLostFocus; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }

		inline float getXpos() const { return xPos; }
		inline float getYpos() const { return yPos; }
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent();
		virtual EventType getEventType() const override { return EventType::WindowMoved; }
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }
	};

}