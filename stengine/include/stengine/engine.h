#ifndef _STENGINE_ENGINE_H_
#define _STENGINE_ENGINE_H_

#include <stutil/util.h>
#include <vector>
#include <type_traits>

namespace stengine {
	/*
	------------------------------------------------------------
		Redefinitions and forward declarations
	------------------------------------------------------------
	*/
	using namespace stutil;
	class ISceneGraph; //defined in -----.h
	class GameObject; //Forward Declaration for Parent pointer
	class Collider; //Forward Declaration for Parent pointer

	/*
	============================================================

		Components

		To create your own components to attach to objects, use the following base example:

		class MyComponent : public Component {
		public:
			MyComponent(GameObject* parent) : Component(parent) {}
			void update() {}

			static const ComponentID ID;
			ComponentID getID() {
				return ID;
			}
		};
		const ComponentID MyComponent::ID = nextComponenetID();

	============================================================
	*/
	typedef unsigned int ComponentID;

	inline static ComponentID nextComponentID() {
		static ComponentID _nextID = 0;
		return _nextID++;
	}


	class Component {
	public:
		static const ComponentID ID;
		const GameObject* parent;

		virtual ~Component() {}
		Component( GameObject* _parent ) {
			parent = _parent;
		}

		virtual ComponentID getID() = 0;
		virtual void update() = 0;
		virtual void onCollision( const Collider* col ) {}
	};



	/*
	============================================================

		GameObject

	All objects inside the engine must derive this class.
	A game object has a position and a number of components that control its behaviour.

	============================================================
	*/
	struct Position {
		mutable int x, y, z;
	};

	class GameObject {
	public:
		GameObject();
		~GameObject();

		void update();
		void onCollision( const Collider* col ) const;
		template<typename C> void		addComponent();
		template<typename C> C*			getComponent();

		Position position;

	private:
		std::vector<Component*>* _components;
	};


	class Collider : public Component {
	public:
		static const ComponentID ID;
		Collider( GameObject* parent );
		virtual ComponentID getID() = 0;
		virtual void update() = 0;
	};

	class ISceneGraph {
	public:
		virtual void addCollider( Collider* obj ) 		= 0;
		virtual void removeCollider( Collider* obj )	= 0;
		virtual void update()							= 0;

	private:
	};

	class Renderer : public Component {
	public:
		static const ComponentID ID;
		Renderer( GameObject* parent );
		virtual ComponentID getID() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
	};

	/*
	============================================================

		GameManager

	All objects inside the engine must derive this class.
	A game object has a position and a number of components that control its behaviour.

	============================================================
	*/
	class GameManager {
	public:
		/*
		------------------------------------------------------------
			Singleton overides
		------------------------------------------------------------
		*/
		GameManager( const GameManager& )               = delete;
		GameManager&  operator=( const GameManager& )   = delete;
		~GameManager();


		static void init();
		static void end();
		static void update();
		static void render();
		static void addObject( GameObject* obj );
		static void addCollider( Collider* obj );
		static void removeCollider( Collider* obj );

	private:
		GameManager();
		static GameManager& instance();

		static GameManager*         _instance;
		std::vector<GameObject*>*   _gameObjects;
		ISceneGraph*				_sceneGraph;

	};
	template<typename C>
	void GameObject::addComponent() {
		static_assert( ( std::is_base_of<Component, C>::value ), "Template Parameter must be of type Component" );
		C* tmp = new C( this );
		_components->push_back( tmp );

		if( std::is_base_of<Collider, C>::value == true )
			GameManager::addCollider( dynamic_cast<Collider*>( tmp ) );
	}

	template<typename C>
	C* GameObject::getComponent() {
		for(auto* obj : *_components)
			if(dynamic_cast<C*>(obj))
				return dynamic_cast<C*>(obj);
		return NULL;
	}
}
#endif