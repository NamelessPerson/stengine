#ifndef _FIXED_GRID_H_
#define _FIXED_GRID_H_

#include "iscenegraph.h"
#include "util/debug.h"

class FixedGrid : public ISceneGraph{
public:
	FixedGrid(int width, int height);
	FixedGrid();
	~FixedGrid();

	void addSceneNode(SceneNode* node);
	SceneNode* removeSceneNode(SceneNode* node);
	void updateSceneNode(SceneNode* node, int x, int y);

	DArray<SceneNode*>* getColliders(SceneNode* node);
	DArray<SceneNode*>* getColliders(int x, int y);
	DArray<SceneNode*>* getColliders(int x, int y, int radius);
	DArray<SceneNode*>* getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);
private:
	DArray<SceneNode*>* graph;
	int width;
	int height;
	int size;

	int getIndex(int x, int y);
};
#endif
