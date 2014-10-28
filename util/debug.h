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
private:
	Debug(){};
	Debug(Debug const&){};
	Debug& operator=(Debug const&){ return *_instance; };
	static Debug* _instance;
};

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
		case UTIL:
			cout << "[UTIL] ";
			break;
		case UNIT:
			break;
		default:
			cout<<"[!!!INVALID CHANNEL!!!] ";
			break;
	}
	cout<<msg<<endl;
}

void Debug::warn(int channel, string msg){
	cout<<"\n====WARNING====\n-->";
	DEBUG_LOG(channel, msg);
	cout << endl;
}

void Debug::err(int channel, string msg){
	cout<<"\n====!!ERROR!!====\n-->";
	DEBUG_LOG(channel, msg);
	cout << endl;
}

void Debug::unit(bool passed, string msg){
	if(passed) cout << "[PASSED] - ";
	else cout << "[FAILED] - ";
	DEBUG_LOG(UNIT, msg);
}

#endif
