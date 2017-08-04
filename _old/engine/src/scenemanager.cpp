#include "engine/scenemanager.h"
#include "util/debug.h"

SceneManager* SceneManager::_instance = 0;

SceneManager::SceneManager(){
	_graph = 0;
}

void SceneManager::tick(float dt){
	DEBUG_LOG(Debug::ENGINE, "SceneManager - Entering Tick");
	unsigned int i;

	for(i = 0; i < controllers.length(); i++)
		controllers.get(i)->tick(dt);
}

void SceneManager::addTickable(ITickable* obj){
	controllers.add(obj);
}

void SceneManager::removeTickable(ITickable* obj){
	unsigned int i;
	for(i = 0; i < controllers.length(); i++){
		if(controllers.get(i) == obj){
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
SceneNode* SceneManager::removeSceneNode(SceneNode* node){
	return _graph->removeSceneNode(node);
}
void SceneManager::updateSceneNode(SceneNode* node, int x, int y){
	return _graph->updateSceneNode(node, x, y);
}

DArray<SceneNode*>* SceneManager::getColliders(SceneNode* node){
	return _graph->getColliders(node);
}
DArray<SceneNode*>* SceneManager::getColliders(int x, int y){
	return _graph->getColliders(x, y);
}
DArray<SceneNode*>* SceneManager::getColliders(int x, int y, int radius){
	return _graph->getColliders(x, y, radius);
}
DArray<SceneNode*>* SceneManager::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2){
	return _graph->getColliders(cornerX1, cornerY1, cornerX2, cornerY2);
}