#ifndef _GRID_ACTOR_H_
#define _GRID_ACTOR_H_

#include <cstring>
#include"SceneManager.h"
#include "Actor/ICollidable.h"

using namespace std;

class GridActor : ICollidable{
public:
	GridActor();
	GridActor(string _name);
	GridActor(string _name, int x, int y);
	SceneNode* getNode();
	string getName();
private:
	string name;
	SceneNode node;
};
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
SceneNode* GridActor::getNode(){
	return &node;
}

string GridActor::getName(){
	return name;
}
#endif
