#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include "engine/dispatcher.h"


/**
 ================================
 	 Event Bus

 Class for keeping track of listeners
 and executing callbacks on events
 ================================
 */
class EventBus : ITickable{
public:
	void pretick(float dt);
	void tick(float dt);
	void posttick(float dt);
	void addListener(IEvent* event, ICallback* callback);
	void removeListener(IEvent* event, ICallback* callback);
	void dispatch(IEvent* event);

	static EventBus* instance();
private:
	EventBus();
	~EventBus();
	Dispatcher bus;
	static EventBus* _instance;
};
#endif
