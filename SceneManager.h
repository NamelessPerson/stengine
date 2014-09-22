#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "GridController.h"
#include "SceneNode.h"
#include "FixedGrid.h"
#include "DataStructs/DArray.h"

class SceneManager{
public:
	void tick(float dt);
	void addTickable(ITickable* obj);
	ISceneGraph* graph();
	static SceneManager* instance();

private:
	ISceneGraph* _graph;
	SceneManager() {};
	DArray<ITickable> controllers;
	static SceneManager* _instance;
};

void SceneManager::tick(float dt){
	int i;

	for(i = 0; i < controllers.length(); i++)
		controllers.get(i)->tick(dt);
}

void SceneManager::addTickable(ITickable* obj){
	controllers.add(obj);
}

ISceneGraph* SceneManager::graph(){
	return _graph;
}

SceneManager* SceneManager::instance(){
	if(_instance == 0) _instance = new SceneManager();
	return _instance;
}
#endif
