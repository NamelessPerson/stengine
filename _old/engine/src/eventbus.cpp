#include "engine/eventbus.h"

EventBus* EventBus::_instance = 0;

EventBus::EventBus(){
	SceneManager::instance()->addTickable(this);
}

EventBus::~EventBus(){

}
//Go through events and make callbacks to listeners
void EventBus::pretick(float dt){
	bus.pretick(dt);
}
void EventBus::tick(float dt){
	bus.tick(dt);
}
void EventBus::posttick(float dt){
	bus.posttick(dt);
}

void EventBus::addListener(IEvent* event, ICallback* callback){
	bus.addListener(event, callback);
}

void EventBus::removeListener(IEvent* event, ICallback* callback){
	bus.removeListener(event, callback);
}

void EventBus::dispatch(IEvent* event){
	bus.dispatch(event);
}

EventBus* EventBus::instance(){
	if(_instance == 0) _instance = new EventBus();
	return _instance;
}
