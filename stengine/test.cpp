#include <stengine/engine.h>
#include <thread>
#include <chrono>

using namespace STEngine;

class TestComponent : public IComponent {
public:
	static const ComponentID ID;

	ComponentID getID() {
		return ID;
	}

	void update(){
		Debug::log("TestComponent Update");
	}
};
const ComponentID TestComponent::ID = nextID();

class TestObject : public GameObject {
public:
	TestObject() {
		addComponent<TestComponent>();
	}
	
	void update() {
		Debug::log( "Game Object Location: " );
		Debug::log( _position.x );
	}
};


int main() {
	GameManager::init();
	GameManager::addObject( new TestObject() );

	while( 1 ) {
		GameManager::update();
		GameManager::render();
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

		return 0;
	}

	return 0;
}