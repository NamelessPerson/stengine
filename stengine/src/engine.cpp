#include <stengine/engine.h>

using namespace STEngine;

const ComponentID IComponent::ID = nextID();

/*
------------------------------------------------------------
    GameObject methods
------------------------------------------------------------
*/
GameObject::GameObject() {
	_components = new std::vector<IComponent*>();
}

GameObject::~GameObject(){
	for(auto* obj : *_components)
		delete obj;
	delete _components;
}

void GameObject::updateComponents(){
	Debug::log("Here");
	for(auto* obj : *_components)
		obj->update();
}


/*
------------------------------------------------------------
    GameManager methods
------------------------------------------------------------
*/
GameManager* GameManager::_instance = 0;

GameManager::GameManager() { 
	_sceneObjects = new std::vector<GameObject*>();
}

GameManager::~GameManager() { 
	delete _sceneObjects;
}

GameManager& GameManager::instance() {
	if( !_instance )
		_instance = new GameManager();

	return *_instance;
}

void GameManager::init() { }

void GameManager::update() {
	GameManager& inst = instance();

	for(auto* obj : *(inst._sceneObjects)){
		obj->updateComponents();
		obj->update();
	}
}
void GameManager::render() { }

void GameManager::addObject( GameObject* obj ) {
	instance()._sceneObjects->push_back(obj);
}