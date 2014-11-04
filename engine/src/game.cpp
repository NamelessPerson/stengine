#include <unistd.h>
#include <ncurses.h>

#include "engine/game.h"
#include "engine/actor/actor.h"
#include "engine/scenemanager.h"
#include "engine/fixedgrid.h"

#include "util/json/jsonparser.h"
#include "util/debug.h"


Game::Game(){
	DEBUG_LOG(Debug::ENGINE, "Initializing Game Object");
	screen.x = 0;
	screen.y = 0;
	screen.width = 1;
	screen.height = 1;
}

void Game::play(){
	JsonParser config;
	//Init Stuff
	config.parse("json/game.json");
	level.init();

	DEBUG_LOG(Debug::ENGINE, "Entering main game loop");
	while(playing){
		update();
		render();
		sleep(1);
	}
}

void Game::update(){
	DEBUG_LOG(Debug::ENGINE, "Entering the update method");
	getmaxyx(stdscr, screen.height, screen.width);
	//SceneManager::instance()->tick(0);
}

void Game::render(){
	DEBUG_LOG(Debug::ENGINE, "Entering the render method");
	int i,j;
	unsigned int k;
	char c;
	short color;
	int depth;
	DArray<SceneNode*>* temp;

	clear();
	start_color();
	
	init_pair(1, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLUE);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	
	attrset(COLOR_PAIR(1));
	attrset(COLOR_PAIR(2));
	attrset(COLOR_PAIR(3));
	attrset(COLOR_PAIR(4));

	for(j = 0; j<screen.height-4; j++){
		move(j,1);
		for(i = 0; i<screen.width-2; i++){
			c = ' ';
			color = 1;
			depth = -1;
			for(k = 0; k < temp->length(); k++){
				temp = SceneManager::instance()->getColliders(i, j);
				if(temp->get(k)->actor && temp->get(k)->actor->renderDepth() > depth){
					c = temp->get(k)->actor->getCharacter();
					color = temp->get(k)->actor->getColor();
					//Only draw the top-most item
					depth = temp->get(k)->actor->renderDepth();
				}
			}
			addch(c | COLOR_PAIR(color));
		}
	}
	mvprintw(screen.height-2,0,"Hello World - This is gonna be over written");
	refresh();

}