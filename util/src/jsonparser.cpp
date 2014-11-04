#include "../json/jsonparser.h"

/*
==============================================
	JsonParser()

Default constructor.
==============================================
*/
JsonParser::JsonParser(){
	head = 0;
}

/*
==============================================
	JsonParser()

Constructs object and then parses filename
==============================================
*/
JsonParser::JsonParser(const string filename){
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
void JsonParser::parse(const string filename){
	if(head) delete head;
	head = new JsonNode();
	head->type = JsonType::OBJ;
	
	ifstream file(filename);
	if(file.is_open()){
		DEBUG_LOG(Debug::UTIL, "JsonParser - Parsing: " + filename);
		head->obj = getObj(file);
	}
	else DEBUG_ERR(Debug::UTIL, "JsonParser - Cannot open file: "+filename);
	file.close();
}

Trie<JsonNode*>* JsonParser::getObj(ifstream &file){
	char c;
	JsonType nextType;
	string nextKey;
	Trie<JsonNode*>* obj = new Trie<JsonNode*>();
	JsonNode* temp;

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
						DEBUG_LOG(Debug::UTIL, "JsonParser - Next type is "+to_string(nextType));
						nextKey = getKey(file);
						DEBUG_LOG(Debug::UTIL, "JsonParser - Next key is " + nextKey);
						temp = new JsonNode();
						switch(nextType){
							case VALUE:
								temp->type = JsonType::VALUE;
								temp->value = getVal(file);
								DEBUG_LOG(Debug::UTIL, "JsonParser - adding value of "+*(temp->value)+" at " + nextKey);
								obj->add(nextKey, temp);
								break;
							case OBJ:
								temp->type = JsonType::OBJ;
								temp->obj = getObj(file);
								DEBUG_LOG(Debug::UTIL, "JsonParser - adding obj at " + nextKey);
								obj->add(nextKey, temp);
								break;
							case ARR:
								temp->type = JsonType::ARR;
								temp->arr = getArr(file);
								DEBUG_LOG(Debug::UTIL, "JsonParser - adding array at " + nextKey);
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

string* JsonParser::getVal(ifstream &file){
	char c = 0;
	string* s = new string();
	while(c <= 32) c = file.get();
	if(c == '"'){
		DEBUG_LOG(Debug::UTIL, "JsonParser - Getting Val of String");
		c = file.get();
		while(c != '"'){
			*s += c;
			c = file.get();
		}
		while(c != ',') c = file.get();
	}
	else{
		DEBUG_LOG(Debug::UTIL, "JsonParser - Getting Val of of type other than string");
		while(c != ','){
			*s += c;
			c = file.get();
		}
	}

	return s;
}

DArray<string*>* JsonParser::getArr(ifstream &file){
	DArray<string*>* arr = new DArray<string*>();
	string* temp = new string();
	char c = 0;

	while(c != '[') c = file.get();
	c = file.get();
	if(c == ']') return arr;

	while(c != ']'){
		temp = new string();
		//ITS A STRING
		if(c == '"'){
			c= file.get();
			while(c != '"'){
				*temp += c;
				c = file.get();
			}
			c = file.get();
		}
		//Something else
		else{
			*temp += c;
			c = file.get();
			
			while(c != ',' && c != ']'){
				*temp += c;
				c = file.get();
			}
		}
		if(c == ',') c = file.get();
		arr->add(temp);
	}

	c = file.get();
	while(c <= 32) c = file.get();
	if(c != ',') DEBUG_WARN(Debug::UTIL, "Expected , but instead: "+to_string(c));

	return arr;
}

JsonType JsonParser::getType(ifstream &file){
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

	DEBUG_ERR(Debug::UTIL, "JsonParser - Cannot get type: Incorrect Formatting. Returning VALUE");
	return JsonType::VALUE;
}

string JsonParser::getKey(ifstream &file){
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

	DEBUG_LOG(Debug::UTIL, "JsonParser - Got key of "+key);
	return key;
	
}

void* JsonParser::get(const string key){
	if(head) return head->get(key);
	DEBUG_WARN(Debug::UTIL, "JsonParser - trying to get item when Head is not initialized; returning null ");
	return 0;
}

void* JsonNode::get(const string key){
	int i = key.find(':');
	if(i == -1) return (void*)(obj->get(key)->value);

	else return obj->get(key.substr(0, i))->get(key.substr(i + 1, key.length() - (i+1)));
}