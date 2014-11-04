#include "engine/level.h"
#include "engine/fixedgrid.h"
#include "engine/actor/tile.h"

#include "util/debug.h"
#include "util/json/jsonparser.h"

int getIndex(int,int,int);

Level::Level(){
	
}
void Level::init(){
	JsonParser config;
	int i,j;
	DEBUG_LOG(Debug::ENGINE, "Level - Intializing Level");
	config.parse("json/level.json");

	int width = stoi(GET_JSTRING(config, "worldwidth"));
	int height = stoi(GET_JSTRING(config, "worldheight"));
	SceneManager::instance()->setGraph(new FixedGrid(width, height));
	Tile** grid = new Tile*[width*height];

	DEBUG_LOG(Debug::ENGINE, "Level - Populating Tiles");
	
	//Fill in Tiles with default
	string defaultTileName = GET_JSTRING(config, "defaulttile");
	Trie<JsonNode*>* defaultTile = GET_JOBJ(config, defaultTileName);
	string color = *defaultTile->get("color")->value;
	char character = (*defaultTile->get("character")->value)[0];

	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			grid[getIndex(i, j, width)] = new Tile(defaultTileName, i, j, character, color);
		}
	}

	//TODO Overwrite with other defined tiles

	DEBUG_LOG(Debug::ENGINE, "Level - Giving Tiles to SceneManager");
	//Place tiles into SceneManager
	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			SceneManager::instance()->addSceneNode(&grid[getIndex(i, j, width)]->node);
		}
	}

}

int getIndex(int x, int y, int width){
	return (y*width) + x;
}