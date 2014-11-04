#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "iscenegraph.h"
#include "../util/datastructs/darray.h"

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
	SceneNode*  removeSceneNode(SceneNode* node);
	void updateSceneNode(SceneNode* node, int x, int y);

	void setGraph(ISceneGraph* graph);

	DArray<SceneNode*>* getColliders(SceneNode* node);
	DArray<SceneNode*>* getColliders(int x, int y);
	DArray<SceneNode*>* getColliders(int x, int y, int radius);
	DArray<SceneNode*>* getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);

private:
	ISceneGraph* _graph;
	SceneManager();
	DArray<ITickable*> controllers;
	static SceneManager* _instance;
};

#endif
