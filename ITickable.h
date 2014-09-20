#ifndef _I_TICKABLE_H_
#define _I_TICKABLE_H_

class ITickable{
public:
	virtual void tick(float dt) = 0;
};

#endif