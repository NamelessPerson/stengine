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
	char c = ' ';
	short color = 1;
	DArray<SceneNode*>* temp;

	clear();
	start_color();
	init_color(7, 139, 69, 19);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	attrset(COLOR_PAIR(1));

	for(j = 0; j<screen.height-4; j++){
		move(j,1);
		for(i = 0; i<screen.width-2; i++){
			c = ' ';
			color = 1;
			for(k = 0; k < temp->length(); k++){
				temp = SceneManager::instance()->getColliders(i, j);
				if(temp->get(k)->actor){
					c = temp->get(k)->actor->getCharacter();
					color = temp->get(k)->actor->getColor();
				}
			}
			addch(c | COLOR_PAIR(color));
		}
	}
	mvprintw(screen.height-2,0,"Hello World - This is gonna be over written");
	refresh();

}