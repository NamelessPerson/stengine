#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Node.h"

template<class E>
class Queue{
	public:
		Queue();
		~Queue();

		bool empty();
		unsigned int size();

		bool queue(E);
		E dequeue();
	private:
		Node<E>* head;
		Node<E>* tail;

		unsigned int _size;
};

template <class E>
Queue<E>::Queue(){
	head = 0;
	tail = 0;
	_size = 0;
}

template <class E>
Queue<E>::~Queue(){
	Node<E>* n = head;
	Node<E>* temp;
	while(n != NULL){
		temp = n;
		n = temp->getNext();
		delete temp;
	}

}

template <class E>
bool Queue<E>::empty(){
	return head == 0;
}

template <class E>
unsigned int Queue<E>::size(){
	return _size;
}

template <class E>
bool Queue<E>::queue(E data){
	Node<E>* tmp;
	_size++;

	if(head == 0){
		head = new Node<E>(data);
		tail = head;
	}

	else{
		tmp = new Node<E>(data);
		tail->setNext(tmp);
		tail = tmp;
	}
	return true;
}

template <class E>
E Queue<E>::dequeue(){
	Node<E>* tmp;
	E rtn;
	if(head == 0) return 0;
	if(tail == head) tail = 0;

	_size--;
	tmp = head;
	head = tmp->getNext();
	rtn = tmp->getData();
	delete tmp;

	return rtn;
}
#endif