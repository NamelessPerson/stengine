#include <stengine/fixedgrid.h>
#include <iostream>


using namespace stengine;

const ComponentID GridSpaceCollider::ID = nextID();

FixedGridGraph::FixedGridGraph( int width, int height ) : _width( width ), _height( height ) {
	_graph = new std::vector<GridSpaceCollider*>[width * height]; //That a lot of memory!!!
}

FixedGridGraph::~FixedGridGraph() {
	delete [] _graph;
}

void FixedGridGraph::addCollider( Collider* obj ) {
	if( obj == NULL ) return;

	if( dynamic_cast<GridSpaceCollider*>( obj ) )
		_graph[obj->parent->position.x + ( obj->parent->position.y * _height )].push_back( dynamic_cast<GridSpaceCollider*>( obj ) );
	else
		debug::err << "Error adding collider" << debug::endl;
}
void FixedGridGraph::removeCollider( Collider* obj ) {}
void FixedGridGraph::update() {
	int x, y;
	// Debug::log( "Begin---------------" );

	//One pass iterating through to update all positions
	for( y = 0; y < _height; y++ ) {
		for( x = 0; x < _width; x++ ) {
			auto& v = _graph[x + ( y * _height )];

			for( auto it = v.begin(); it != v.end(); ) {

				if( ( *it )->parent->position.x != x || ( *it )->parent->position.y != y ) {
					// std::cout << "Graph: " << x << ", " << y << "; Object: " << ( *it )->parent->position.x << ", " << ( *it )->parent->position.y << std::endl;
					_graph[( *it )->parent->position.x + ( ( *it )->parent->position.y * _height )].push_back( *it );
					it = v.erase( it );
				}
				else
					++it;

			}
		}
	}

	//Second pass to check collisions
	for(x = 0; x < _width * _height; x++){
		if(_graph[x].size() > 1){
			// Debug::log("Collision Detected");
			//For each collision call onCollision
			for(Collider* obj : _graph[x])
				for(Collider* col : _graph[x])
					if(obj != col)
						obj->parent->onCollision(col);
		}
	}
}
