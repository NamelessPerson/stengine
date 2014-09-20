#ifndef _FIXED_GRID_H_
#define _FIXED_GRID_H_

#include "DArray.h"
#include "ISceneGraph.h"

class FixedGrid : ISceneGraph{
public:
	FixedGrid(unsigned int width, unsigned int height);
	FixedGrid();
	~FixedGrid();

	void addSceneNode(SceneNode node);
	void removeSceneNode(SceneNode node);
	void updateSceneNode(SceneNode node, int x, int y);

	DArray<SceneNode> getColliders(SceneNode node);
	DArray<SceneNode> getColliders(int x, int y);
	DArray<SceneNode> getColliders(int x, int y, int radius);
	DArray<SceneNode> getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);
private:
	SceneNode* graph;
	unsigned int width;
	unsigned int height;
};

FixedGrid::FixedGrid(){
	width = 8;
	height = 8;
	unsigned int size = width * height;
	graph = new SceneNode[size];

}

FixedGrid::FixedGrid(unsigned int _width, unsigned int _height){
	width = _width;
	height = _height;
	unsigned int size = width * height;
	graph = new SceneNode[size];

}

FixedGrid::~FixedGrid(){
	delete [] graph;
}
#endif