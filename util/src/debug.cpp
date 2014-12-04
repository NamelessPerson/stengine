#include "../debug.h"

Debug* Debug::_instance = 0;

Debug::Debug(){
	out = &cout;
}

Debug* Debug::instance(){
	if(!_instance){
		_instance = new Debug();
	}
	return _instance;
}

void Debug::log(int channel, string msg){
	if(muted[channel]) return;
	switch(channel){
		case GAMEPLAY:
			*out<<"[GAMEPLAY] ";
			break;
		case DATASTRUCTS:
			*out<<"[DATASTRUCTS] ";
			break;
		case DEBUG:
			*out<<"[DEBUG] ";
			break;
		case UTIL:
			*out << "[UTIL] ";
			break;
		case UNIT:
			break;
		case ENGINE:
			*out << "[ENGINE] ";
			break;
		default:
			*out<<"[!!!INVALID CHANNEL!!!] ";
			break;
	}
	*out<<msg<<endl;
}

void Debug::warn(int channel, string msg){
	if(muted[channel]) return;
	*out<<"\n====WARNING====\n-->";
	DEBUG_LOG(channel, msg);
	*out << endl;
}

void Debug::err(int channel, string msg){
	if(muted[channel]) return;
	*out<<"\n====!!ERROR!!====\n-->";
	DEBUG_LOG(channel, msg);
	*out << endl;
}

void Debug::unit(bool passed, string msg){
	if(muted[UNIT]) return;
	if(passed) *out << "[PASSED] - ";
	else *out << "[FAILED] - ";
	DEBUG_LOG(UNIT, msg);
}

void Debug::setOutput(ostream* newOutput){
	out = newOutput;
}
ostream* Debug::getOutput(){
	return out;
}

void Debug::mute(int channel){
	muted[channel] = true;
}
void Debug::unMute(int channel){
	muted[channel] = false;
}