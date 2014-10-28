#ifndef _GRID_ACTOR_H_
#define _GRID_ACTOR_H_

#include <cstring>
#include"../scenemanager.h"
#include "icollidable.h"

using namespace std;

class GridActor : ICollidable{
public:
	GridActor();
	GridActor(string _name);
	GridActor(string _name, int x, int y);
	SceneNode* getNode();
	string getName();
	SceneNode node;
private:
	string name;
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

string GridActor::getName(){
	return name;
}
#endif
