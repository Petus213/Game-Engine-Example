/*! \file Keyboard_Events.h
*\brief This file contains all of the keyboard events
*/
#pragma once
#include "Events/events.h"

namespace Engine {

	/*! \class KeyEvent
	*\breif The key event class will return what type of key has been pressed. 
	*/
	class KeyEvent : public Event {
	protected:
		int m_keycode; //!< integer m_keycode
		KeyEvent(int keycode) : m_keycode(keycode) {} //!< Constructor
	public:
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; } //!< getCategoryFlags, returns Keyboard Events and Input

		inline int getKeycode() const { return m_keycode; } //!< this will return keycode, which key has been pressed
	};
	/*! \class KeyPressedEvent
	*\breif The key pressed event class will return when a key has been pressed.
	*/
	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeatcount; //!< Integer m_repeatCount
	public:
		KeyPressedEvent(int keycode, int repeatcount) : KeyEvent(keycode), m_repeatcount(repeatcount) {} //!< Constructor

		static EventType getStaticType() { return EventType::KeyPressed; } //!< getStaticType, this will return which key has been pressed
		virtual EventType getEventType() const override { return EventType::KeyPressed; } //!< getEventType, this will return the Event for Key Pressed

		inline int getRepeatCount() const { return m_repeatcount; } //!< getRepeatCount, gets how many times the key was repeatedly pressed

	};
	/*! \class KeyReleasedEvent
	*\breif The key released event class will return when a key has been released.
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	private:
		
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode){} //!< constructor

		static EventType getStaticType() { return EventType::KeyReleased; } //!< getStaticType, returns when the key has been released
		virtual EventType getEventType() const { return EventType::KeyReleased; } //!< getEventType, will return which Event Type has triggered

		inline int getKeycode() const { return m_keycode; } //!< This will get the keycode of which key has been released
	};
	/*! \class KeyTypedEvent
	*\breif The key typed event class will return when keys have been typed.
	*useful for text boxes.
	*/
	class KeyTypedEvent : public KeyEvent
	{

	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {} //!< constructor
		 
		static EventType getStaticType() { return EventType::KeyTyped; } //!< getStaticType, returns when a key has been typed
		virtual EventType getEventType() const { return EventType::KeyTyped; } //!< getEventType, returns which Event type has been triggered

		inline int getKeycode() const { return m_keycode; } //!< This will return the keycode of which key has been typed
	};




}