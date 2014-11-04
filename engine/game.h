#ifndef _GAME_H_
#define _GAME_H_

#include "level.h"

struct Screen{
	int x,y;
	int width, height;
};

class Game{
public:
	Game();
	void play();
private:
	Screen screen;
	bool playing;
	Level level;
	void update();
	void render();
};

#endif