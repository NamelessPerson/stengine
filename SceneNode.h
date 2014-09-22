#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

class SceneNode{
public:
	int getX();
	int getY();
	void setX(int x);
	void setY(int Y);
private:
	int x,y;
	void* actor;

};

#endif
