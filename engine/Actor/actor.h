#ifndef _ACTOR_H_
#define _ACTOR_H_

class ICollidable{
	//virtual bool collides(ICollidable*);
};

class IDrawable{
public:
	virtual char getCharacter() = 0;
	virtual short getColor() = 0;
	virtual int renderDepth() = 0;
};

#endif
