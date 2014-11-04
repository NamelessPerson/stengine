#include "engine/fixedgrid.h"

FixedGrid::FixedGrid(){
	DEBUG_LOG(Debug::ENGINE, "Creating FixedGrid of size 8x8");
	width = 8;
	height = 8;
	size = width * height;
	graph = new DArray<SceneNode*>[size];

}

FixedGrid::FixedGrid(int _width, int _height){
	DEBUG_LOG(Debug::ENGINE, "Creating FixedGrid of size "+to_string(_width)+"x"+to_string(_height));
	width = _width;
	height = _height;
	int size = width * height;
	graph = new DArray<SceneNode*>[size];

}

FixedGrid::~FixedGrid(){
	delete [] graph;
}

void FixedGrid::addSceneNode(SceneNode* node){
	DEBUG_LOG(Debug::ENGINE, "Adding scene node at "+to_string(node->x)+", "+to_string(node->y));
	graph[getIndex(node->x, node->y)].add(node);
}

SceneNode* FixedGrid::removeSceneNode(SceneNode* node){
	if(graph[getIndex(node->x, node->y)].remove(node)) return node;
	return 0;
}

void FixedGrid::updateSceneNode(SceneNode* node, int x, int y){
	if(x >= width || y >= height) return;

	graph[getIndex(node->x, node->y)].remove(node);
	node->x = x;
	node->y = y;
	addSceneNode(node);
}

DArray<SceneNode*>* FixedGrid::getColliders(SceneNode* node){
	return &graph[getIndex(node->x, node->y)];
}
DArray<SceneNode*>* FixedGrid::getColliders(int x, int y){
	return &graph[getIndex(x,y)];
}
//Not implemented since they're not needed for simulation. TODO later
DArray<SceneNode*>* FixedGrid::getColliders(int x, int y, int radius){
	return 0;
}
DArray<SceneNode*>* FixedGrid::getColliders(int cornerX1, int cornerY1, int cornerX2, int cornerY2){
	return 0;
}

int FixedGrid::getIndex(int x, int y){
	return (y*width) + x;
}