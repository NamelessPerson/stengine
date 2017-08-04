#include "engine/actor/gridactor.h"
#include "util/debug.h"

GridActor::~GridActor(){
	
}

GridActor::GridActor(){
	name = "Default Name";
	node.actor = this;
	node.x = 0;
	node.y = 0;
	DEBUG_LOG(Debug::GAMEPLAY,"GridActor - New Actor "+name+" spawned at "+to_string(node.x)+", "+to_string(node.y));
}
GridActor::GridActor(string _name){
	name = _name;
	node.actor = this;
	node.x = 0;
	node.y = 0;
	DEBUG_LOG(Debug::GAMEPLAY,"GridActor - New Actor "+name+" spawned at "+to_string(node.x)+", "+to_string(node.y));
}
GridActor::GridActor(string _name, int x, int y){
	name = _name;
	node.actor = this;
	node.x = x;
	node.y = y;
	DEBUG_LOG(Debug::GAMEPLAY,"GridActor - New Actor "+name+" spawned at "+to_string(node.x)+", "+to_string(node.y));
}

string GridActor::getName(){
	DEBUG_LOG(Debug::ENGINE, "GridActor - Returning name of "+name);
	return name;
}

char GridActor::getCharacter(){
	DEBUG_LOG(Debug::ENGINE, "GridActor - Returning character of D for "+name);
	return 'D';
}
short GridActor::getColor(){
	DEBUG_LOG(Debug::ENGINE, "GridActor - Returning color of 1 for "+name);
	return 1;
}

int GridActor::renderDepth(){
	DEBUG_LOG(Debug::ENGINE, "GridActor - Returning depth of 3 for "+name);
	return 3;
}
SceneNode* GridActor::getNode(){
	DEBUG_LOG(Debug::ENGINE, "GridActor - Returning SceneNode of "+name);
	return &node;
}