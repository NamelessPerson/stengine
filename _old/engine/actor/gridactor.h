#ifndef _GRID_ACTOR_H_
#define _GRID_ACTOR_H_

#include <string>
#include "engine/scenemanager.h"
#include "actor.h"

class GridActor : public ICollidable, public IDrawable, public ISelectable{
public:
	GridActor();
	GridActor(string _name);
	GridActor(string _name, int x, int y);
	~GridActor();
	
	SceneNode* getNode();
	string getName();
	
	SceneNode node;

	int renderDepth();
	char getCharacter();
	short getColor();
//private:
	string name;
	string type;

	char render_character;
	string color;
	bool selectable = false;

	float thirst, sleep, gold;
	int wallet;
};

#endif
