#pragma once
#include "Events/events.h"

namespace Engine {

	class KeyEvent : public Event {
	protected:
		int m_keycode;
		KeyEvent(int keycode) : m_keycode(keycode) {}
	public:
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

		inline int getKeycode() const { return m_keycode; }
	};

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

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		//KeyReleasedEvent(){}

		virtual EventType getEventType() const override { return EventType::KeyReleased; }
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard; }

		static EventType getStaticType() { return EventType::KeyReleased; }

		//inline int getKeycode() const { return i_KeyCode; }
	};

	class KeyTypedEvent : public KeyEvent
	{
	private:
		int i_KeyCode;
	public:
		//KeyTypedEvent(){}

		virtual EventType getEventType() const override { return EventType::KeyTyped; }
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard; }

		static EventType getStaticType() { return EventType::KeyTyped; }

		inline int getKeycode() const { return i_KeyCode; }
	};




}