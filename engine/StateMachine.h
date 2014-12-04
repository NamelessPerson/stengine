#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "dispatcher.h"
#include "engine/actor/actor.h"
#include "engine/actor/gridactor.h"

class IState{
	virtual IState* handleInput(GridActor*) = 0;
};

class IStateMachine : public ITickable{
public:
	virtual void pretick(float dt) = 0;
	virtual void tick(float dt) = 0;
	virtual void posttick(float dt) = 0;
private:
	IState* _currentState;
};

#endif