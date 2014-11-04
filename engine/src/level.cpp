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
	unsigned int k,l;
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
	short color = (short)stoi(*defaultTile->get("color")->value);
	char character = (*defaultTile->get("character")->value)[0];

	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			grid[getIndex(i, j, width)] = new Tile(defaultTileName, i, j, character, color);
		}
	}

	//TODO Generate other Tiles
	DArray<string*>* tiles = GET_JARR(config, "othertiles");
	DArray<string*>* current_tile;
	string temp;
	for(k = 0; k < tiles->length(); k++){
		current_tile = GET_JARR(config, *tiles->get(k)+":locations");
		for(l = 0; l < current_tile->length(); l++){
			temp = *current_tile->get(l);
			i = stoi(temp.substr(0, temp.find(',')));
			j = stoi(temp.substr(temp.find(',')+1, temp.length()));
			delete grid[getIndex(i,j,width)];
			grid[getIndex(i,j,width)] = new Tile(*tiles->get(k),i,j, (GET_JSTRING(config, *tiles->get(k)+":character"))[0],stoi(GET_JSTRING(config, *tiles->get(k)+":color")));
		}
	}

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