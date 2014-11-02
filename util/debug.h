#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <string>
#include <iostream>

//Macros to make logging easier
#define DEBUG_LOG(a,b) Debug::instance()->log(a,b)
#define DEBUG_WARN(a,b) Debug::instance()->warn(a,b)
#define DEBUG_ERR(a,b) Debug::instance()->err(a,b)
#define DEBUG_UNIT(a,b) Debug::instance()->unit(a,b)

using namespace std;

/*
============================================================
	Debug

	Debug logger class. 
============================================================
*/
class Debug{
public:
	static Debug* instance();

	void log(int, string);
	void warn(int, string);
	void err(int, string);
	void unit(bool, string);
	enum{
		GAMEPLAY, DATASTRUCTS, DEBUG, UNIT, UTIL
	};

	void setOutput(ostream*);
	ostream* getOutput();

	void mute(int channel);
	void unMute(int channel);

private:
	Debug();
	Debug(Debug const&){};
	Debug& operator=(Debug const&){ return *_instance; };
	static Debug* _instance;
	ostream* out;
	bool muted[5];
};

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


#endif
