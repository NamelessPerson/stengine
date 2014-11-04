#include "engine/actor/gridactor.h"

GridActor::GridActor(){
	name = "";
	node.actor = this;
}
GridActor::GridActor(string _name){
	name = _name;
	node.actor = this;
}
GridActor::GridActor(string _name, int x, int y){
	name = _name;
	node.actor = this;
	node.x = x;
	node.y = y;
}

string GridActor::getName(){
	return name;
}

char GridActor::getCharacter(){
	return ' ';
}
short GridActor::getColor(){
	return 1;
}

int GridActor::renderDepth(){
	return 0;
}