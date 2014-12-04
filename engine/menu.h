#ifndef _MENU_H_
#define _MENU_H_

#include "util/datastructs/stack.h"

class Menu{

};

class MenuManager : public IDrawable{
public:
	MenuManager();
	void render();
private
	Stack<Menu*> menus;
};

#endif