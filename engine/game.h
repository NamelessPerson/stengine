#ifndef _GAME_H_
#define _GAME_H_

#include <ctime>
#include "level.h"

struct Screen{
	int x,y;
	int width, height;
};

struct Player{
	int gold;
	Player(){gold = 500;};
};

class Game{
public:
	Game();
	void play();
	static Player player;
private:
	Screen screen;
	bool playing;
	Level level;
	void update();
	void render();
	clock_t delta;
};

#endif