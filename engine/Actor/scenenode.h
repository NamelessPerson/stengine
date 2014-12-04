#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "engine/actor/actor.h"

struct SceneNode{
	int x, y;
	IDrawable* actor;
};

#endif