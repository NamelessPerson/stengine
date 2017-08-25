#ifndef _STENGINE_ENGINE_H_
#define _STENGINE_ENGINE_H_

/*
============================================================

	ComponentID 

original code by reddogstone:
https://reddogstone.wordpress.com/2010/09/24/unique-class-id-in-c/

To create your own game component declare your class like so:

	class MyComponent : public GameComponent<MyComponent>

============================================================
*/

typedef unsigned int ComponentID;
 
static ComponentID nextID() {
    static ComponentID _nextID = 0;
    return _nextID++;
}
 
class IComponent {
    virtual ComponentID getID() = 0;
};
 
template <typename Derived>
class GameComponent : public IComponent {
    static ComponentID _id;
 
public:
    static ComponentID StaticID() {
        return _id;
    }
 
    ComponentID getID() {
        return _id;
    }
};
 
template <typename Derived>
ComponentID GameComponent<Derived>::_id = nextID();
 
// class Position : public Component<Position> {};

/*
Using this a a stickynote for design ideas
Engine Design:

class GameManager;
class GameObject;
class FixedGridSceneGraph;
*/

#endif