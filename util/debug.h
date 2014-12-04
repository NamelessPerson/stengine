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
		GAMEPLAY, DATASTRUCTS, DEBUG, UNIT, UTIL, ENGINE
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

#endif
