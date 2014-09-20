/*
 * Debug.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: jphilli2
 */
#include "Debug.h"

Debug* Debug::_instance = 0;

Debug* Debug::instance(){
	if(!_instance){
		_instance = new Debug();
	}
	return _instance;
}

void Debug::log(int channel, string msg){
	switch(channel){
		case GAMEPLAY:
			cout<<"[GAMEPLAY] ";
			break;
		case DATASTRUCTS:
			cout<<"[DATASTRUCTS] ";
			break;
		case DEBUG:
			cout<<"[DEBUG] ";
			break;
		default:
			cout<<"[!!!INVALID CHANNEL!!!] ";
			break;
	}
	cout<<msg<<endl;
}

void Debug::warn(int channel, string msg){
	cout<<"==WARNING==";
	DEBUG_LOG(channel, "yoo");
}

void Debug::err(int channel, string msg){
	cout<<"==!!ERROR!!==\n-->";
	DEBUG_LOG(channel, "yoo");
	cout<<"==!!ERROR!!=="<<endl;
}



