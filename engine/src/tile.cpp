#include "engine/actor/tile.h"

Tile::Tile(string _name, int x, int y, char character, string _color){
	name = _name;
	node.actor = this;
	node.x = x;
	node.y = y;
	render_character = character;
	color = _color;
}

string Tile::getName(){
	return name;
}

char Tile::getCharacter(){
	return render_character;
}
short Tile::getColor(){
	return 2;
}

int Tile::renderDepth(){
	return 0;
}