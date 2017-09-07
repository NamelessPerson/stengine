#ifndef _STENGINE_ENGINE_H_
#define _STENGINE_ENGINE_H_

#include <stutil/util.h>
#include <vector>
#include <type_traits>

namespace STEngine {
	/*
	------------------------------------------------------------
		Redefinition of useful util items
	------------------------------------------------------------
	*/
	typedef STUtil::Debug Debug;

	/*
	============================================================

		Components

		To create your own components to attach to objects, use the following base example:

		class MyComponent : public IComponent { 
		public: 
			static const ComponentID ID; 
			ComponentID getID() { 
				return ID; 
			} 
		}; 
		const ComponentID MyComponent::ID = nextID();

	============================================================
	*/
	typedef unsigned int ComponentID;

	inline static ComponentID nextID() {
		static ComponentID _nextID = 0;
		return _nextID++;
	}

	class IComponent {
	public:
		static const ComponentID ID;
		virtual ComponentID getID() = 0;
		virtual void update() = 0;
		virtual ~IComponent() {};
	};



	/*
	============================================================

		GameObject

	All objects inside the engine must derive this class.
	A game object has a position and a number of components that control its behaviour.

	============================================================
	*/

	struct Position {
		float x, y, z;
	};

	class GameObject {
	public:
		virtual void update()   = 0;

		GameObject();
		~GameObject();
		template<typename C> void			addComponent();
		template<typename C> IComponent*	getComponent();
		void updateComponents();
		
		Position _position;

	private:
		std::vector<IComponent*>* _components;
	};

	template<typename C>
	void GameObject::addComponent() {
		static_assert((std::is_base_of<IComponent, C>::value), "Template Parameter must be of type IComponent");
		_components->push_back( new C() );
	}

	/*
	============================================================

		ISceneGraph

	TODO
	============================================================
	*/
	class ISceneGraph {
	public:
		virtual void update() = 0;
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
		static void update();
		static void render();
		static void addObject( GameObject* obj );

	private:
		GameManager();
		static GameManager& instance();

		static GameManager*         _instance;
		std::vector<GameObject*>*   _sceneObjects;
	};
}
#endif