#include <stengine/engine.h>
#include <stengine/fixedgrid.h>
#include <thread>
#include <chrono>

using namespace STEngine;

class TestComponent : public Component {
public:
	static const ComponentID ID;

	TestComponent(GameObject* parent) : Component(parent) {}

	ComponentID getID() {
		return ID;
	}

	void update(){
		parent->position.x++;
	}

	void onCollision(const Collider* col){
		Debug::log("Collision Happened");
	}
};
const ComponentID TestComponent::ID = nextID();

int main() {
	int loops = 0;

	GameManager::init();

	GameObject* testObject = new GameObject();
	testObject->addComponent<TestComponent>();
	testObject->addComponent<GridSpaceCollider>();
	GameManager::addObject( testObject );

	GameObject* obstacle = new GameObject();
	obstacle->addComponent<GridSpaceCollider>();
	obstacle->position.x = 2;
	GameManager::addObject( obstacle );


	while( loops++ < 2 ) {
		GameManager::update();
		GameManager::render();
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
	}

	return 0;
}