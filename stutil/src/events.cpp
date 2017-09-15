#include <stutil/events.h>

using namespace stutil;

Dispatcher::Dispatcher() {
	_listeners = new std::unordered_map<EventID, std::unordered_set<IEventListener*>*>();
}

Dispatcher::~Dispatcher() {
	//Clear out allocated sets first
	for(auto iter = _listeners->begin(); iter != _listeners->end(); ++iter){
		delete iter->second;
	}
	
	delete _listeners;
}

void Dispatcher::addListener( EventID event, IEventListener* listener ) {
	if( listener != NULL ) {
		auto search = _listeners->find( event );

		if( search != _listeners->end() )
			search->second->emplace( listener );
		else {
			std::unordered_set<IEventListener*>* tmp = new std::unordered_set<IEventListener*>();
			tmp->emplace( listener );
			_listeners->emplace( event, tmp );
		}
	}
}

void Dispatcher::removeListener( EventID event, IEventListener* listener ) {
	if( listener != NULL ) {
		auto search = _listeners->find( event );

		if( search != _listeners->end() )
			search->second->erase( listener );
	}
}

void Dispatcher::dispatch( EventID event ) {
	auto search = _listeners->find( event );

	if( search != _listeners->end() ) {
		for( IEventListener* listener : *search->second )
			listener->onEvent( event );
	}
}