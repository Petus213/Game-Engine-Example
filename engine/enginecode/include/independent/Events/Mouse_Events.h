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
		int m_button; //!< integer m_button
		MouseEvent(int button) : m_button(button) {} //!< constructor
	public:
		virtual int getCategoryFlags() const override { return EventCategoryMouseButton | EventCategoryInput; } //!< getCategoryFlags, returns EventCategories for input and mouse button
		
		inline int getKeycode() const { return m_button; } //!< finds the keycode associated with which button was pressed
	};
	/*! \class MouseButtonPressedEvent
	*\breif The mouse button pressed event class will return when a mouse button has been pressed.
	*/
	class MouseButtonPressedEvent : public MouseEvent
	{
	private:
		int m_repeatCount; //!< integer m_repeatCount
	public:
		MouseButtonPressedEvent(int button) : MouseEvent(button){} //!< constructor

		virtual EventType getEventType() const override { return EventType::MouseButtonPressed; } //!< getEventType, returns which mouse button was pressed
		static EventType getStaticType() { return EventType::MouseButtonPressed; } //!< getStaticType, returns which mouse button was pressed

		inline int getMouseButton() const { return m_repeatCount; } //!< getMouseButton, returns repeat count
	};
	/*! \class MouseButtonReleasedEvent
	*\breif The mouse button released event class will return when a mouse button has been released.
	*/
	class MouseButtonReleasedEvent : public MouseEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseEvent(button){} //!< constructor

		virtual EventType getEventType() const override { return EventType::MouseButtonReleased; } //!< getEventType, returns when a mouse button has been released
		static EventType getStaticType() { return EventType::MouseButtonReleased; } //!< getStaticType, returns when a mouse button has been released

		inline int getMouseButton() const { return m_button; } //!< getMouseButton, returns the button which has been pressed
	};
	/*! \class MouseMovedEvent
	*\breif The mouse moved event class will return a value for when the mouse cursor has been moved.
	* particularly useful for first person games or other camera controls, for example.
	*/
	class MouseMovedEvent : public Event
	{
	private:
		float m_YOffset;//!< Float variables X Offset
		float m_XOffset;//!< Float variables Y Offset 

	public:
		MouseMovedEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {} //!< constructor
		 
		virtual EventType getEventType() const override { return EventType::MouseMoved; } //!< getEventType, returns when the mouse has been moved
		virtual int getCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; } //!< getCategoryFlags, returns when a mouse has moved and the input

		static EventType getStaticType() { return EventType::MouseMoved; } //!< getStaticTypem returns when the mouse has moved

		inline int getMouseXoffset() const { return m_XOffset; } //!< returns when the mouse has been moved on the X axis
		inline int getMouseYoffset() const { return m_YOffset; } //!< returns when the mouse has been moved on the Y axis
	};
	/*! \class MouseScrolledEvent
	*\breif The mouse scrolled event class will return when the mouse wheel has been scrolled.
	* a good use for this would be to zoom the camera in and out.
	*/
	class MouseScrolledEvent : public Event
	{
	private:
		float m_XOffset; //!< float variables X offset
		float m_YOffset; //!< float variables Y offset
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {} //!< constructor

		virtual EventType getEventType() const override { return EventType::MouseScrolled; } //<! getEventType, returns if mouse has been scrolled
		virtual int getCategoryFlags() const override { return EventCategoryMouse; } //!< getCategoryFlags, returns the EventCategory for mouse

		static EventType getStaticType() { return EventType::MouseScrolled; } //!< getStaticType, returns if the mouse has been scrolled
		 
		inline int getMouseXoffset() const { return m_XOffset; } //!< returns when the mouse has scrolled either up or down
		inline int getMouseYoffset() const { return m_YOffset; } //!< returns when the mouse has scrolled either up or down
	};
}