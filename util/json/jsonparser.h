/*
 * JParser.h
 *
 *  Created on: Sep 21, 2014
 *      Author: jphilli2
 */

#ifndef _J_PARSER_H_
#define _J_PARSER_H_

#include "../datastructs/darray.h"
#include "../datastructs/trie.h"
#include "../debug.h"
#include <string>
#include <fstream>

//Some easier to use macros

#define GET_JSTRING(a, b) *(static_cast<string*>(a.get(b)))
#define GET_JARR(a, b) static_cast<DArray<string*>*>(a.get(b))
#define GET_JOBJ(a, b) static_cast<Trie<JNode*>*>(a.get(b))

/*
============================================================
	JSonType

Enumeration for keeping track of JsonTypes

TODO: Add support for all types separately
============================================================
*/
enum JsonType{ VALUE, OBJ, ARR };

/*
============================================================
	JNode

A special node class for holding pointers to data retrieved
from a JSon File. Can either contain a Value, an Array, or
an Object. Use intelligently.
============================================================
*/
struct JNode{
	JsonType type;
	union {
		string* value;
		Trie<JNode*>* obj;
		DArray<string*>* arr;
	};
	void* get(const string);
};


/*
============================================================
	JParser

Class for Parsing JSon files.

BE WARNED: There is little type safety. Use intelligently

You must call parse before use. It then stores the object
generated which can then be gotten using the Get method.
Please only use with properly formatted JSon that is inside
a main object. Everything MUST be followed by a comma to
mark the end.
============================================================
*/
class JParser{
public:
	JParser();
	JParser(const string);
	void parse(const string);

	void* get(const string);
private:
	JNode* head;
	Trie<JNode*>* getObj(ifstream &file);
	DArray<string*>* getArr(ifstream &file);
	string* getVal(ifstream &file);
	string getKey(ifstream &file);
	JsonType getType(ifstream &file);
};

/*
==============================================
	JParser()

Default constructor.
==============================================
*/
JParser::JParser(){
	head = 0;
}

/*
==============================================
	JParser()

Constructs object and then parses filename
==============================================
*/
JParser::JParser(const string filename){
	head = 0;
	parse(filename);
}

/*
==============================================
	void parse(const string filename)

Parses filename and stores data. Must be called
before get() can be used.
==============================================
*/
void JParser::parse(const string filename){
	if(head) delete head;
	head = new JNode();
	head->type = JsonType::OBJ;
	
	ifstream file(filename);
	if(file.is_open()){
		DEBUG_LOG(Debug::UTIL, "JParser - Parsing: " + filename);
		head->obj = getObj(file);
	}
	else DEBUG_ERR(Debug::UTIL, "JParser - Cannot open file: "+filename);
	file.close();
}

Trie<JNode*>* JParser::getObj(ifstream &file){
	char c;
	JsonType nextType;
	string nextKey;
	Trie<JNode*>* obj = new Trie<JNode*>();
	JNode* temp;

	while(!file.eof()){
		c = file.get();
		//Ignore control characters and spaces
		if(c > 32){
			//Start of object
			if(c == '{'){
				while(!file.eof()){
					c = file.get();
					//End of object
					if(c == '}'){
						while(c != ',' && !file.eof()) c = file.get();

						return obj;
					}
					else if(c == '"'){
						nextType = getType(file);
						DEBUG_LOG(Debug::UTIL, "JParser - Next type is "+to_string(nextType));
						nextKey = getKey(file);
						DEBUG_LOG(Debug::UTIL, "JParser - Next key is " + nextKey);
						temp = new JNode();
						switch(nextType){
							case VALUE:
								temp->type = JsonType::VALUE;
								temp->value = getVal(file);
								DEBUG_LOG(Debug::UTIL, "JParser - adding value of "+*(temp->value)+" at " + nextKey);
								obj->add(nextKey, temp);
								break;
							case OBJ:
								temp->type = JsonType::OBJ;
								temp->obj = getObj(file);
								DEBUG_LOG(Debug::UTIL, "JParser - adding obj at " + nextKey);
								obj->add(nextKey, temp);
								break;
							case ARR:
								temp->type = JsonType::ARR;
								temp->arr = getArr(file);
								DEBUG_LOG(Debug::UTIL, "JParser - adding array at " + nextKey);
								obj->add(nextKey, temp);
								break;
							default:
								break;
						}
					}
					else if(c > 32){
						DEBUG_ERR(Debug::UTIL, "Improperly formatted JSON: not expecting " + to_string(c));
						return 0;
					}
				}
			}
			else{
				DEBUG_ERR(Debug::UTIL, "Improperly formatted JSON");
				return 0;
			}
		}
	}
	return obj;
}

string* JParser::getVal(ifstream &file){
	char c = 0;
	string* s = new string();
	while(c <= 32) c = file.get();
	if(c == '"'){
		DEBUG_LOG(Debug::UTIL, "JParser - Getting Val of String");
		c = file.get();
		while(c != '"'){
			*s += c;
			c = file.get();
		}
		while(c != ',') c = file.get();
	}
	else{
		DEBUG_LOG(Debug::UTIL, "JParser - Getting Val of of type other than string");
		while(c != ','){
			*s += c;
			c = file.get();
		}
	}

	return s;
}

DArray<string*>* JParser::getArr(ifstream &file){
	DArray<string*>* arr = new DArray<string*>();
	string* temp = new string();
	char c = 0;

	while(c != '[') c = file.get();
	c = file.get();
	if(c == ']') return arr;

	while(c != ']'){
		temp = new string();
		*temp += c;
		c = file.get();
		
		while(c != ',' && c != ']'){
			*temp += c;
			c = file.get();
		}
		if(c == ',') c = file.get();
		arr->add(temp);
	}

	c = file.get();
	while(c <= 32) c = file.get();
	if(c != ',') DEBUG_WARN(Debug::UTIL, "Expected , but instead: "+to_string(c));

	return arr;
}

JsonType JParser::getType(ifstream &file){
	streampos pos = file.tellg();
	char c = 0;
	
	//Skip Key
	while(c != ':') c = file.get();

	while(!file.eof()){
		c = file.get();
		if(c == '[' || c == '{' || c == ',') file.seekg(pos);
		if(c == '[') return JsonType::ARR;
		else if(c == '{') return JsonType::OBJ;
		else if (c == ',')return JsonType::VALUE;
	}

	DEBUG_ERR(Debug::UTIL, "JParser - Cannot get type: Incorrect Formatting. Returning VALUE");
	return JsonType::VALUE;
}

string JParser::getKey(ifstream &file){
	string key = "";
	char c = 0;
	//File should be on opening " already
	c = file.get();
	while(c != '"'){
		key += c;
		c = file.get();
	}
	//Set cursor to start of value
	while(c != ':') c = file.get();

	DEBUG_LOG(Debug::UTIL, "JParser - Got key of "+key);
	return key;
	
}

void* JParser::get(const string key){
	if(head) return head->get(key);
	DEBUG_WARN(Debug::UTIL, "JParser - trying to get item when Head is not initialized; returning null ");
	return 0;
}

void* JNode::get(const string key){
	int i = key.find(':');
	if(i == -1) return (void*)(obj->get(key)->value);

	else return obj->get(key.substr(0, i))->get(key.substr(i + 1, key.length() - (i+1)));
}
#endif
