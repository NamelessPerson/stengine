#ifndef _STENGINE_FIXED_GRID_H_
#define _STENGINE_FIXED_GRID_H_

#include <stengine/engine.h>

namespace STEngine {

	class GridSpaceCollider : public Collider {
	public:
		GridSpaceCollider( GameObject* parent ) : Collider( parent ) {}

		static const ComponentID ID;
		ComponentID getID() {
			return ID;
		}

		void update() {};
	};

	//This is a really bad SceneGraph but it is quick and simple
	class FixedGridGraph : public ISceneGraph {
	public:
		FixedGridGraph(int width, int height);
		~FixedGridGraph();
		void addCollider( Collider* obj );
		void removeCollider( Collider* obj );
		void update();
	private:
		const int _width;
		const int _height;
		std::vector<GridSpaceCollider*>* _graph;
	};

}

#endif