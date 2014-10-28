#ifndef _EVENT_BUS_H_
#define _EVENT_BUS_H_

#include <cstdlib>
#include "DataStructs/DArray.h"
#include "DataStructs/Queue.h"
#include "SceneManager.h"

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
	void tick(float dt);
	void addListener(IEvent* event, ICallback* callback);
	void removeListener(IEvent* event, ICallback* callback);
	void dispatch(IEvent* event);
private:
	struct s_listener{
		ICallback* callback;
		string eventType;
	};
	DArray<s_listener> listeners;
	Queue<IEvent*> events;
};

Dispatcher::Dispatcher(){
	SceneManager::instance()->addTickable(this);
}

Dispatcher::~Dispatcher(){

}
//Go through events and make callbacks to listeners
void Dispatcher::tick(float dt){
	IEvent* temp;
	int i;

	while(!events.empty()){
		temp = events.dequeue();
		for(i = 0; i < listeners.length(); i++){
			//Something happened - Got to go do some controller logic
			if(listeners.get(i)->eventType == temp->getType()) listeners.get(i)->callback->execute(temp);
		}
	}
}

void Dispatcher::addListener(IEvent* event, ICallback* callback){
	s_listener* l = new s_listener;
	l->callback = callback;
	l->eventType = event->getType();
	listeners.add(l);
}

void Dispatcher::removeListener(IEvent* event, ICallback* callback){
	int i;
	//NOTE: Will remove duplicates
	for(i = 0; i < listeners.length(); i++){
		if(listeners.get(i)->callback == callback && listeners.get(i)->eventType == event->getType()){
			listeners.remove(i);
			//Things were shifted
			i--;
		}
	}
}

void Dispatcher::dispatch(IEvent* event){
	events.queue(event);
}

#endif
