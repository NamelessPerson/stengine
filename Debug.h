#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <iostream>
#include <cstring>

#define DEBUG_LOG(a,b) Debug::instance()->log(a,b)
#define DEBUG_WARN(a,b) Debug::instance()->warn(a,b)
#define DEBUG_ERR(a,b) Debug::instance()->err(a,b)

using namespace std;

class Debug{
public:
	static Debug* instance();

	void log(int, string);
	void warn(int, string);
	void err(int, string);
	enum{
		GAMEPLAY, DATASTRUCTS, DEBUG,
	};
private:
	Debug(){};
	Debug(Debug const&){};
	Debug& operator=(Debug const&){};
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

#endif
