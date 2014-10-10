#ifndef _FIXED_GRID_H_
#define _FIXED_GRID_H_

#include "ISceneGraph.h"

class FixedGrid : public ISceneGraph{
public:
	FixedGrid(unsigned int width, unsigned int height);
	FixedGrid();
	~FixedGrid();

	void addSceneNode(SceneNode* node);
	void removeSceneNode(SceneNode* node);
	void updateSceneNode(SceneNode* node, int x, int y);

	DArray<SceneNode> getColliders(SceneNode* node);
	DArray<SceneNode> getColliders(int x, int y);
	DArray<SceneNode> getColliders(int x, int y, int radius);
	DArray<SceneNode> getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2);
private:
	DArray<SceneNode>* graph;
	unsigned int width;
	unsigned int height;
	unsigned int size;

	unsigned int getIndex(int x, int y);
};

FixedGrid::FixedGrid(){
	width = 8;
	height = 8;
	size = width * height;
	graph = new DArray<SceneNode>[size];

}

FixedGrid::FixedGrid(unsigned int _width, unsigned int _height){
	width = _width;
	height = _height;
	unsigned int size = width * height;
	graph = new DArray<SceneNode>[size];

}

FixedGrid::~FixedGrid(){
	delete [] graph;
}

void FixedGrid::addSceneNode(SceneNode* node){
	graph[getIndex(node->x, node->y)].add(node);
}

void FixedGrid::removeSceneNode(SceneNode* node){
	graph[getIndex(node->x, node->y)].remove(node);
}

void FixedGrid::updateSceneNode(SceneNode* node, int x, int y){
	if(x >= width || y >= height) return;

	graph[getIndex(node->x, node->y)].remove(node);
	node->x = x;
	node->y = y;
	addSceneNode(node);
	

}

DArray<SceneNode> FixedGrid::getColliders(SceneNode* node){
	return graph[getIndex(node->x, node->y)];
}
DArray<SceneNode> FixedGrid::getColliders(int x, int y){
	return graph[getIndex(x,y)];
}
DArray<SceneNode> FixedGrid::getColliders(int x, int y, int radius){}
DArray<SceneNode> FixedGrid::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2){}

unsigned int FixedGrid::getIndex(int x, int y){
	return (y*width) + x;
}
#endif
