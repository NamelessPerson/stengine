#ifndef _STACK_H_
#define _STACK_H_

#include "DArray.h"

template <class E>
class Stack{
public:
	Stack();
	~Stack();

	bool push(E);
	bool push(E*);
	bool empty();

	E* pop();
	E* peek();

	unsigned int size();
private:
	DArray<E>* stack;
};

template <class E>
Stack<E>::Stack(){
	stack = new DArray<E>();
}

template <class E>
Stack<E>::~Stack(){
	delete stack;
}

template <class E>
bool Stack<E>::push(E item){
	return stack->add(item);
}

template <class E>
bool Stack<E>::push(E* item){
	return stack->add(item);
}

template <class E>
bool Stack<E>::empty(){
	return stack->length() == 0;
}

template <class E>
E* Stack<E>::pop(){
	return stack->remove(-1);
}

template <class E>
E* Stack<E>::peek(){
	return stack->get(-1);
}

template <class E>
unsigned int Stack<E>::size(){
	return stack->length();
}
#endif
