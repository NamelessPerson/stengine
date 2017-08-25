#include "stutil/debug.h"
#include <iostream>
#include <iomanip>

using namespace STUtil;

/*
------------------------------------------------------------
	Debug Class Private Methods
------------------------------------------------------------
*/
Debug* Debug::_instance = 0;
std::ostream* Debug::Channel::defaultOutput = &std::cout;

Debug::Debug() {
	channels = new std::unordered_map<std::string, Channel*>();
	channels->emplace( std::string( "Debugger" ), new Channel( "Debugger", NULL ) );
	channels->emplace( "Unknown", new Channel( "Unknown", NULL ) );
	channels->emplace( "Log", new Channel( "Log", NULL ) );

	defaultChannel = channels->find( "Log" )->second;
}

Debug& Debug::instance() {
	if( !_instance )
		_instance = new Debug();

	return *_instance;
}
Debug::Channel& Debug::operator[]( const std::string& key ) {
	return *defaultChannel;
}

/*
------------------------------------------------------------
	Debug Class Public Methods
------------------------------------------------------------
*/
bool Debug::addChannel( const std::string channelName ) {
	Debug& inst = Debug::instance();

	if( inst.channels->find( channelName ) == inst.channels->end() ) {
		inst.channels->emplace( channelName, new Channel( channelName, NULL ) );
		return true;
	}

	return false;
}

bool Debug::addChannel( const std::string channelName, std::ostream& output ) {
	std::unordered_map<std::string, Channel*>* channels = Debug::instance().channels;

	if( channels->find( channelName ) == channels->end() ) {
		channels->emplace( channelName, new Channel( channelName, &output ) );
		return true;
	}

	return false;
}
void Debug::setDefault( std::ostream& output ) {
	Channel::defaultOutput = &output;
}

Debug::Channel& Debug::channel( const std::string channelName ) {
	std::unordered_map<std::string, Channel*>* channels = Debug::instance().channels;
	auto rtn =  channels->find( channelName );

	if( rtn == channels->end() ) {
		channels->find( "Debugger" )->second->log( "Unknown channel " + channelName );
		return * ( channels->find( "Unknown" )->second );
	}
	else
		return * ( rtn->second );
}

/*
------------------------------------------------------------
	Channel Class Methods
------------------------------------------------------------
*/
Debug::Channel::Channel( std::string name, std::ostream* output ) {
	_name = name;
	_output = output;
}

void Debug::Channel::mute() {
	muted = true;
}
void Debug::Channel::unmute() {
	muted = false;
}