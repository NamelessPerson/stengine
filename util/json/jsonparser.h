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
#define GET_JOBJ(a, b) static_cast<Trie<JsonNode*>*>(a.get(b))

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
	JsonNode

A special node class for holding pointers to data retrieved
from a JSon File. Can either contain a Value, an Array, or
an Object. Use intelligently.
============================================================
*/
struct JsonNode{
	JsonType type;
	union {
		string* value;
		Trie<JsonNode*>* obj;
		DArray<string*>* arr;
	};
	void* get(const string);
};


/*
============================================================
	JsonParser

Class for Parsing JSon files.

BE WARNED: There is little type safety. Use intelligently

You must call parse before use. It then stores the object
generated which can then be gotten using the Get method.
Please only use with properly formatted JSon that is inside
a main object. Everything MUST be followed by a comma to
mark the end.
============================================================
*/
class JsonParser{
public:
	JsonParser();
	JsonParser(const string);
	void parse(const string);

	void* get(const string);
private:
	JsonNode* head;
	Trie<JsonNode*>* getObj(ifstream &file);
	DArray<string*>* getArr(ifstream &file);
	string* getVal(ifstream &file);
	string getKey(ifstream &file);
	JsonType getType(ifstream &file);
};


#endif
