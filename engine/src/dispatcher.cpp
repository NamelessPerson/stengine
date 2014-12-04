#include "engine/dispatcher.h"

Dispatcher::Dispatcher(){
	SceneManager::instance()->addTickable(this);
}

Dispatcher::~Dispatcher(){

}
//Go through events and make callbacks to listeners
void Dispatcher::pretick(float dt){}
void Dispatcher::tick(float dt){
	IEvent* temp;
	unsigned int i;

	while(!events.empty()){
		temp = events.dequeue();
		for(i = 0; i < listeners.length(); i++){
			//Something happened - Got to go do some controller logic
			if(listeners.get(i)->eventType == temp->getType()) listeners.get(i)->callback->execute(temp);
		}
	}
}
void Dispatcher::posttick(float dt){}

void Dispatcher::addListener(IEvent* event, ICallback* callback){
	s_listener* l = new s_listener;
	l->callback = callback;
	l->eventType = event->getType();
	listeners.add(l);
}

void Dispatcher::removeListener(IEvent* event, ICallback* callback){
	unsigned int i;
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
