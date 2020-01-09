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
		int m_keycode;
		KeyEvent(int keycode) : m_keycode(keycode) {}
	public:
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

		inline int getKeycode() const { return m_keycode; }
	};
	/*! \class KeyPressedEvent
	*\breif The key pressed event class will return when a key has been pressed.
	*/
	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeatcount;
	public:
		KeyPressedEvent(int keycode, int repeatcount) : KeyEvent(keycode), m_repeatcount(repeatcount) {}

		static EventType getStaticType() { return EventType::KeyPressed; }
		virtual EventType getEventType() const override { return EventType::KeyPressed; }

		inline int getRepeatCount() const { return m_repeatcount; }

	};
	/*! \class KeyReleasedEvent
	*\breif The key released event class will return when a key has been released.
	*/
	class KeyReleasedEvent : public KeyEvent
	{
	private:
		
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode){}

		static EventType getStaticType() { return EventType::KeyReleased; }
		virtual EventType getEventType() const { return EventType::KeyReleased; }

		inline int getKeycode() const { return m_keycode; }
	};
	/*! \class KeyTypedEvent
	*\breif The key typed event class will return when keys have been typed.
	*useful for text boxes.
	*/
	class KeyTypedEvent : public KeyEvent
	{

	public:
		KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

		static EventType getStaticType() { return EventType::KeyTyped; }
		virtual EventType getEventType() const { return EventType::KeyTyped; }

		inline int getKeycode() const { return m_keycode; }
	};




}