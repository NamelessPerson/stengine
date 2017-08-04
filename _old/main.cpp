#include <ncurses.h>
#include <unistd.h>
#include <fstream>

#include "util/debug.h"
#include "engine/game.h"


int main(){
	Debug::instance()->setOutput(new ofstream("log.log", std::ofstream::out));
	
	Game g;
	g.play();

	endwin();
	return 0;
}

void initCurses(){
	initscr();
	if(!has_colors() || !can_change_color()){
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	noecho();
	nodelay(stdscr, TRUE);	
	curs_set(false);
}
