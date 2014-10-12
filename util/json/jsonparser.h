/*
 * JParser.h
 *
 *  Created on: Sep 21, 2014
 *      Author: jphilli2
 */

#ifndef _J_PARSER_H_
#define _J_PARSER_H_

#include "../DataStructs/Trie.h"
#include "../Debug.h"
#include <fstream>

using namespace std;

class JObject{
public:
	JObject(string key);
	string* get(string key);
private:
	string key;
	string* val;
	int elements;
	JObject** children;
};

class JParser{
public:
	JObject* parse(const char*);
private:

};

JObject* JParser::parse(const char* filename){
	char c;

	ifstream file(filename, std::ifstream::in);
	if(file.is_open()){
		while(!file.eof()){
			c = file.get();
			//Ignore control characters and spaces
			if(c > 32){
				//Start of object
				if(c == '{'){
					c = file.get();
					while(!file.eof()){
						if(c>32){

						}
					}
				}
				else{
					DEBUG_ERR(Debug::DEBUG, "Improperly formatted JSON");
				}
			}
		}
	}
	else DEBUG_ERR(Debug::DEBUG, "Cannot open file");
	file.close();
	return 0;
}

#endif
