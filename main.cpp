#include <ncurses.h>
#include <unistd.h>


int main(){
	initscr();
	noecho();
	curs_set(false);

	sleep(1);

	endwin();
	return 0;
}
