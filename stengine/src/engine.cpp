#include <stengine/engine.h>
#include <stengine/fixedgrid.h>
#include <ncurses.h>

using namespace stengine;

const ComponentID Component::ID = nextComponentID();
const ComponentID Collider::ID = nextComponentID();

/*
------------------------------------------------------------
    GameObject methods
------------------------------------------------------------
*/
GameObject::GameObject() {
	_components = new std::vector<Component*>();
}

GameObject::~GameObject() {
	for( auto* obj : *_components )
		delete obj;

	delete _components;
}

void GameObject::update() {
	for( auto* obj : *_components )
		obj->update();
}

void GameObject::onCollision( const Collider* col ) const {
	for( auto* obj : *_components )
		obj->onCollision( col );
}


/*
------------------------------------------------------------
    GameManager methods
------------------------------------------------------------
*/
GameManager* GameManager::_instance = 0;

GameManager::GameManager() {
	_gameObjects = new std::vector<GameObject*>();
	_sceneGraph = new FixedGridGraph( 100, 100 );
}

GameManager::~GameManager() {
	delete _gameObjects;
}

GameManager& GameManager::instance() {
	if( !_instance )
		_instance = new GameManager();

	return *_instance;
}

void GameManager::init() { 
	initscr();
	if(!has_colors() || !can_change_color()){
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	noecho();
	nodelay(stdscr, TRUE);	
	curs_set(false);
}
void GameManager::end() { 
	endwin();
}

void GameManager::update() {
	GameManager& inst = instance();

	for( auto* obj : * ( inst._gameObjects ) )
		obj->update();

	inst._sceneGraph->update();

}
void GameManager::render() {
	GameManager& inst = instance();
	clear();

	for( auto* obj : * ( inst._gameObjects ) ){
		Renderer* ren = obj->getComponent<Renderer>();
		if(ren)
			ren->render();
	}

	refresh();
}

void GameManager::addObject( GameObject* obj ) {
	instance()._gameObjects->push_back( obj );
}

void GameManager::addCollider( Collider* obj ) {
	GameManager& inst = instance();
	inst._sceneGraph->addCollider( obj );
}
void GameManager::removeCollider( Collider* obj ) {
	GameManager& inst = instance();
	inst._sceneGraph->removeCollider( obj );
}

/*
------------------------------------------------------------
    Component methods
------------------------------------------------------------
*/
Collider::Collider( GameObject* parent ) : Component( parent ) { }
Renderer::Renderer( GameObject* parent ) : Component( parent ) { }