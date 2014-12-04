#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_

#include <cstdlib>
#include "../util/datastructs/darray.h"
#include "../util/datastructs/queue.h"
#include "scenemanager.h"

using namespace std;

/**
 ================================
 	 IEvent

 Interface for events used by listeners
 ================================
 */
class IEvent{
public:
	virtual string getType() = 0;
};

/**
 ================================
 	 ICallback

 Interface for Listeners to be added to a dispatcher
 ================================
 */
class ICallback{
public:
	virtual void execute(IEvent *event) = 0;
};

/**
 ================================
 	 Dispatcher

 Class for keeping track of listeners
 and executing callbacks on events
 ================================
 */
class Dispatcher : ITickable{
public:
	Dispatcher();
	~Dispatcher();
	void pretick(float dt);
	void tick(float dt);
	void posttick(float dt);
	void addListener(IEvent* event, ICallback* callback);
	void removeListener(IEvent* event, ICallback* callback);
	void dispatch(IEvent* event);
private:
	struct s_listener{
		ICallback* callback;
		string eventType;
	};
	DArray<s_listener*> listeners;
	Queue<IEvent*> events;
};
#endif
