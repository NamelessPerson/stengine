#ifndef _DWARF_CONTROLLER_H_
#define _DWARF_CONTROLLER_H_

#include "engine/statemachine.h"

class DwarfController : public IStateMachine{
public:
	DwarfController();
	void pretick(float dt);
	void tick(float dt);
	void posttick(float dt);
private:
	GridActor actor;
};

#endif