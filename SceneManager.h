#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "GridController.h"
#include "SceneNode.h"
#include "FixedGrid.h"
#include "DArray.h"

class SceneManager{
public:
	void tick(float dt);
	void addTickable(GridController obj);
	void addSceneNode(SceneNode node);
private:
	SceneManager() {};
	FixedGrid graph;
	DArray<GridController*> controllers;
	static SceneManager* _instance;
};

void SceneManager::tick(float dt){
	int i;

	for(i = 0; i < controllers.length(); i++)
		controllers.get(i)->tick(dt);
}

void SceneManager::addTickable(GridController obj){
	controllers.add(&obj);
}

void SceneManager::addSceneNode(SceneNode node){
	//TODO
}
#endif
