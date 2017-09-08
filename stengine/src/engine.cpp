#include <stengine/engine.h>
#include <stengine/fixedgrid.h>

using namespace STEngine;

const ComponentID Component::ID = nextID();
const ComponentID Collider::ID = nextID();

/*
------------------------------------------------------------
    GameObject methods
------------------------------------------------------------
*/
GameObject::GameObject() {
	_components = new std::vector<Component*>();
}

GameObject::~GameObject(){
	for(auto* obj : *_components)
		delete obj;
	delete _components;
}

void GameObject::update(){
	for(auto* obj : *_components)
		obj->update();
}

void GameObject::onCollision(const Collider* col) const{
	for(auto* obj : *_components)
		obj->onCollision(col);
}


/*
------------------------------------------------------------
    GameManager methods
------------------------------------------------------------
*/
GameManager* GameManager::_instance = 0;

GameManager::GameManager() { 
	_gameObjects = new std::vector<GameObject*>();
	_sceneGraph = new FixedGridGraph(100, 100);
}

GameManager::~GameManager() { 
	delete _gameObjects;
}

GameManager& GameManager::instance() {
	if( !_instance )
		_instance = new GameManager();

	return *_instance;
}

void GameManager::init() { }

void GameManager::update() {
	GameManager& inst = instance();

	for(auto* obj : *(inst._gameObjects))
		obj->update();
	inst._sceneGraph->update();
	
}
void GameManager::render() { }

void GameManager::addObject( GameObject* obj ) {
	instance()._gameObjects->push_back(obj);
}

void GameManager::addCollider( Collider* obj ){
	GameManager& inst = instance();
	inst._sceneGraph->addCollider(obj);
}
void GameManager::removeCollider( Collider* obj ){
	GameManager& inst = instance();
	inst._sceneGraph->removeCollider(obj);
}

/*
------------------------------------------------------------
    GameManager methods
------------------------------------------------------------
*/
Collider::Collider( GameObject* parent ) : Component( parent ){
// 	GameManager::addCollider(this);
}
