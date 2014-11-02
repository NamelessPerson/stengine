#ifndef _STACK_H_
#define _STACK_H_

#include "darray.h"
/*
============================================================
	Stack

This is a traditional LIFO container implemented as a wrapper
over a DArray.
============================================================
*/
template <class E>
class Stack{
public:
	Stack();
	Stack(unsigned int size);

	bool push(E);
	bool empty();

	E pop();
	E peek();

	unsigned int size();
private:
	DArray<E> stack;
};

/*
==============================================
Stack()

Default Constructor
==============================================
*/
template <class E>
Stack<E>::Stack(){
	
}

/*
==============================================
	Stack(unsigned int size)

Constructs a Stack with default amount size
allocated.
==============================================
*/
template <class E>
Stack<E>::Stack(unsigned int size){
	stack(size);
}

/*
==============================================
	bool push(E item)

Places item into the stack.
==============================================
*/
template <class E>
bool Stack<E>::push(E item){
	return stack.add(item);
}

/*
==============================================
	bool empty()

Returns whether or not there are any items
currently in the stack
==============================================
*/
template <class E>
bool Stack<E>::empty(){
	return stack.length() == 0;
}

/*
==============================================
	E pop()

Removes the last item pushed into the Stack and
returns it.
==============================================
*/
template <class E>
E Stack<E>::pop(){
	return stack.remove(-1);
}

/*
==============================================
	E peek()

Returns the last item pushed into the Stack
without removing it.
==============================================
*/
template <class E>
E Stack<E>::peek(){
	return stack.get(-1);
}

/*
==============================================
	unsigned int size()

Returns the number of items currently in the
Stack
==============================================
*/
template <class E>
unsigned int Stack<E>::size(){
	return stack.length();
}
#endif
