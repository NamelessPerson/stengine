#include <stengine/engine.h>
#include <stutil/util.h>

using namespace STUtil;

class IEventListener {
public:
	virtual void onEvent() = 0;
};

class ListenerOne : public virtual IEventListener {
public:
	ListenerOne() {
		Debug::log( "One" );
	}
	virtual void onEvent() = 0;
};

class ListenerTwo : public virtual IEventListener {
public:
	ListenerTwo() {
		Debug::log( "Two" );
	}
	virtual void onEvent() = 0;
};

class Object : public ListenerOne, public ListenerTwo {
public:
	Object() {
		Debug::log( "Object" );
	}
	void onEvent() {
		Debug::log( "Event" );
	}
};

int main() {
	Object obj;
	obj.onEvent();

	return 0;
}