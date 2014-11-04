#include <ncurses.h>
#include <unistd.h>
#include <fstream>

#include "util/debug.h"
#include "engine/game.h"


int main(){
	Debug::instance()->setOutput(new ofstream("log.log", std::ofstream::out));
	initscr();
	if(!has_colors()){
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	noecho();
	curs_set(false);

	Game g;
	g.play();

	endwin();
	return 0;
}
