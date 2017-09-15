#ifndef _STUTIL_EVENTS_H_
#define _STUTIL_EVENTS_H_

#include <unordered_map>
#include <unordered_set>

namespace stutil {

	/*
	============================================================

		Events

	ID Code is originally by reddogstone:
		https://reddogstone.wordpress.com/2010/09/24/unique-class-id-in-c/

	To create new event you can define them as such:

		class MyEvent : Event<MyEvent> {}

	For now there is no reason to put any data in the class but that will most likely change.
	You can register a listener using:

		Dispatcher dispatch;
		dispatch.addListener( MyEvent::ID(), myListener );
	============================================================
	*/

	typedef unsigned int EventID;

	inline static EventID nextID() {
		static EventID _nextID = 0;
		return _nextID++;
	}

	class IEvent {
		virtual EventID getID() = 0;
	};

	template <typename Derived>
	class Event : public IEvent {
		static EventID _id;

	public:
		static EventID ID() {
			return _id;
		}

		EventID getID() {
			return _id;
		}
	};

	template <typename Derived>
	EventID Event<Derived>::_id = nextID();

	class IEventListener {
	public:
		virtual void onEvent( EventID event ) = 0;
	};

	/**
	 ================================
	 	 Dispatcher

	 Class for keeping track of listeners
	 and executing callbacks on events
	 ================================
	 */
	class Dispatcher {
	public:
		Dispatcher();
		~Dispatcher();
		void addListener( EventID event, IEventListener* listener );
		void removeListener( EventID event, IEventListener* listener );
		void dispatch( EventID event );
	private:
		std::unordered_map<EventID, std::unordered_set<IEventListener*>*>* _listeners;
	};

}

#endif