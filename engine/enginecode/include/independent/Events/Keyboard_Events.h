#pragma once
#include "Events/events.h"

namespace Engine {

	class KeyPressedEvent : public Event
	{
	private:
		int i_KeyCode;
		int i_RepeatCount;
	public:
		KeyPressedEvent();

		virtual EventType getEventType() const override { return EventType::KeyPressed; }
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard; }

		static EventType getStaticType() { return EventType::KeyPressed; }

		inline int getKeycode() const { return i_KeyCode; }
		inline int getRepeatCount() const { return i_RepeatCount; }

	};

	class KeyReleasedEvent : public Event
	{
	private:
		int i_KeyCode;
	public:
		KeyReleasedEvent();

		virtual EventType getEventType() const override { return EventType::KeyReleased; }
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard; }

		static EventType getStaticType() { return EventType::KeyReleased; }

		inline int getKeycode() const { return i_KeyCode; }
	};

	class KeyTypedEvent : public Event
	{
	private:
		int i_KeyCode;
	public:
		KeyTypedEvent();

		virtual EventType getEventType() const override { return EventType::KeyTyped; }
		virtual int getCategoryFlags() const override { return EventCategoryKeyboard; }

		static EventType getStaticType() { return EventType::KeyTyped; }

		inline int getKeycode() const { return i_KeyCode; }
	};




}