#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "ISceneGraph.h"
#include "DataStructs/DArray.h"

class ITickable{
public:
	virtual void tick(float dt) = 0;
};

class SceneManager{
public:
	void tick(float dt);
	void addTickable(ITickable* obj);
	void removeTickable(ITickable* obj);
	static SceneManager* instance();

	void addSceneNode(SceneNode* node);
	void removeSceneNode(SceneNode* node);
	void updateSceneNode(SceneNode* node, int x, int y);

	void setGraph(ISceneGraph* graph);

	DArray<SceneNode> getColliders(SceneNode* node);
	DArray<SceneNode> getColliders(int x, int y);
	DArray<SceneNode> getColliders(int x, int y, int radius);
	DArray<SceneNode> getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);

private:
	ISceneGraph* _graph;
	SceneManager();
	DArray<ITickable*> controllers;
	static SceneManager* _instance;
};

SceneManager::SceneManager(){
	_graph = 0;
}

void SceneManager::tick(float dt){
	int i;

	for(i = 0; i < controllers.length(); i++)
		(*(controllers.get(i)))->tick(dt);
}

void SceneManager::addTickable(ITickable* obj){
	controllers.add(obj);
}

void SceneManager::removeTickable(ITickable* obj){
	int i;
	for(i = 0; i < controllers.length(); i++){
		if((*(controllers.get(i))) == obj){
			controllers.remove(i);
			//Should not be duplicates!!
			return;
		}
	}
}

void SceneManager::setGraph(ISceneGraph* graph){
	_graph = graph;
}


SceneManager* SceneManager::instance(){
	if(_instance == 0) _instance = new SceneManager();
	return _instance;
}

void SceneManager::addSceneNode(SceneNode* node){
	return _graph->addSceneNode(node);
}
void SceneManager::removeSceneNode(SceneNode* node){
	return _graph->removeSceneNode(node);
}
void SceneManager::updateSceneNode(SceneNode* node, int x, int y){
	return _graph->updateSceneNode(node, x, y);
}

DArray<SceneNode> SceneManager::getColliders(SceneNode* node){
	return _graph->getColliders(node);
}
DArray<SceneNode> SceneManager::getColliders(int x, int y){
	return _graph->getColliders(x, y);
}
DArray<SceneNode> SceneManager::getColliders(int x, int y, int radius){
	return _graph->getColliders(x, y, radius);
}
DArray<SceneNode> SceneManager::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2){
	return _graph->getColliders(cornerX1, cornerY1, cornerX2, cornerY2);
}

#endif
