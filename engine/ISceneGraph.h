#ifndef _I_SCENE_GRAPH_H_
#define _I_SCENE_GRAPH_H_

#include "actor/scenenode.h"
#include "../util/datastructs/darray.h"

/**
==============================================
	ISceneGraph

Interface to be implemented for SceneGraphs
==============================================
**/
class ISceneGraph{
public:
	virtual void addSceneNode(SceneNode* node) = 0;
	virtual SceneNode* removeSceneNode(SceneNode* node) = 0;
	virtual void updateSceneNode(SceneNode* node, int x, int y) = 0;
	
	virtual DArray<SceneNode*>* getColliders(SceneNode* node) = 0;
	virtual DArray<SceneNode*>* getColliders(int x, int y) = 0;
	virtual DArray<SceneNode*>* getColliders(int x, int y, int radius) = 0;
	virtual DArray<SceneNode*>* getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2) = 0;
};

#endif
