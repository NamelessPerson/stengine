#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "engine/scenemanager.h"
#include "actor.h"

class Tile : public IDrawable{
public:
	Tile(string _name, int x, int y, char character, string _color);
	
	SceneNode* getNode();
	string getName();
	
	SceneNode node;

	int renderDepth();
	char getCharacter();
	short getColor();
private:
	string name;
	char render_character;
	string color;
};

#endif