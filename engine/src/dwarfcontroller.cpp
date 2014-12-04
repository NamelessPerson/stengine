#include "engine/controller/dwarfcontroller.h"
#include "util/debug.h"

DwarfController::DwarfController(){
	//actor = GridActor();
	SceneManager::instance()->addSceneNode(actor.getNode());
	delta = clock();
}

void DwarfController::pretick(float dt){
	
}
void DwarfController::tick(float dt){
	DEBUG_LOG(Debug::GAMEPLAY,"fuck"+to_string(dt-delta));
	if(dt-delta > 5){
		DEBUG_LOG(Debug::GAMEPLAY,"fuck2");

		SceneManager::instance()->updateSceneNode(actor.getNode(),actor.getNode()->x+1,actor.getNode()->y);
		DEBUG_LOG(Debug::GAMEPLAY,"DwarfController - Actor "+actor.name+" moved to "+to_string(actor.getNode()->x)+", "+to_string(actor.getNode()->y));
		delta = dt;	
	}
}
void DwarfController::posttick(float dt){
	
}