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

#endif
