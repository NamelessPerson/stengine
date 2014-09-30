#ifndef _EVENT_BUS_H_
#define _EVENT_BUS_H_

#include <cstdlib>
#include "ITickable.h"
#include "DataStructs/DArray.h"
#include "DataStructs/Queue.h"
#include "SceneManager.h"

using namespace std;

class IEvent{
public:
	virtual string getType() = 0;
};

class ICallback{
public:
	virtual void execute(IEvent *event) = 0;
};

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
void Dispatcher::tick(float dt){
	IEvent* temp;
	int i;

	while(!events.empty()){
		temp = events.dequeue();
		for(i = 0; i < listeners.length(); i++){
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
	for(i = 0; i < listeners.length(); i++){
		if(listeners.get(i)->callback == callback && listeners.get(i)->eventType == event->getType()){
			listeners.remove(i);
			i--;
		}
	}
}

void Dispatcher::dispatch(IEvent* event){
	events.queue(event);
}

#endif
