/*! \file Window_Events.h
*\brief This file contains all of the Window events
*/
#pragma once
#include "Events/events.h"

namespace Engine {

	/*! \class WindowCloseEvent
	*\breif The window close event class will close the current window.
	*/
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {} //!< destructor

		EventType getEventType() const override { return EventType::WindowClose; } //!< gets event type from EventType class
		int getCategoryFlags() const override { return EventCategoryWindow; } //!< integer getCategoryFlags

		static EventType getStaticType() { return EventType::WindowClose;  } //!< gets static type from EventType class
	};
	/*! \class WindowResizeEvent
	*\breif The window resize event class will resize the current window.
	* useful when desiging a game with different resolutions. 
	*/
	class WindowResizeEvent : public Event
	{
	private:
		int m_width; //!< integer width
		int m_height; //!< integer height

	public:
		WindowResizeEvent(int width, int height) : m_width(width), m_height(height) {} //!< constructor

		virtual EventType getEventType() const override { return EventType::WindowResize; } //!< get Event Type from EventType
		virtual int getCategoryFlags() const override { return EventCategoryWindow; } //!< intget getCategoryFlags
		
		static EventType getStaticType() { return EventType::WindowResize; } //!< gets static type from EventType class

		inline int getWidth() const { return m_width; } //!< Integer for width, returns m_width
		inline int getHeight() const { return m_height; } //!< Integer for height, returns m_height
	};
	/*! \class WindowFocusEvent
	*\breif The window focus event class will acknowledge when the current window is not the main view.
	* For instance, when a player is in another window, the game could pause when this is returned.
	*/
	class WindowFocusEvent : public Event
	{
	private:

	public:
		WindowFocusEvent() {} //!< constructor
		virtual EventType getEventType() const override { return EventType::WindowFocus; }//!< get Event Type from EventType
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }//!< intget getCategoryFlags

		static EventType getStaticType() { return EventType::WindowFocus; } //!< gets static type from EventType class

	};
	/*! \class WindowLostFocusEvent
	*\breif The window lost focus event class will acknowledge when the current window is not the main view.
	*/
	class WindowLostFocusEvent : public Event
	{
	private:
		float xPos; //!< float xPosition
		float yPos; //!< float yPosition
	public:
		WindowLostFocusEvent(){} //!< constructor
		virtual EventType getEventType() const override { return EventType::windowLostFocus; }//!< get Event Type from EventType
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }//!< intget getCategoryFlags

		static EventType getStaticType() { return EventType::windowLostFocus; }//!< gets static type from EventType class

		inline float getXpos() const { return xPos; } //!< float getXpos, returns xPosition
		inline float getYpos() const { return yPos; } //!< float getYpos, returns yPosition
	};
	/*! \class WindowMovedEvent
	*\brief The Window Moved Event will return a value when it has been moved.
	*/
	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(){} //!< constructor
		virtual EventType getEventType() const override { return EventType::WindowMoved; }//!< get Event Type from EventType
		virtual int getCategoryFlags() const override { return EventCategoryWindow; }//!< intget getCategoryFlags

		static EventType getStaticType() { return EventType::WindowMoved; }//!< gets static type from EventType class
	};

}