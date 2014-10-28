#ifndef _GRID_CONTROLLER_H_
#define _GRID_CONTROLLER_H_


#include <string>

#include "../util/debug.h"
#include "scenemanager.h"
#include "actor/gridactor.h"

class GridController : public ITickable{
public:
	void tick(float dt);
private:
	DArray<GridActor*> actors;
	float time;
	static const int TICK = 2000;
};
void GridController::tick(float dt){
	GridActor* temp;
	int i;

	if(dt) time += dt;
	if(time >= TICK){
		temp = new GridActor("name", 0, 0);
		actors.add(temp);
		SceneManager::instance()->addSceneNode(temp->getNode());
		DEBUG_LOG(Debug::GAMEPLAY, "Actor " + temp->getName() + " spawned at " + to_string(temp->getNode()->x) + ", " to_string(temp->getNode()->y));
		time -= TICK;
	}
}
#endif
