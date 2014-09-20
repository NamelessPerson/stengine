#ifndef _NODE_H_
#define _NODE_H_


template<class E>
class Node{
public:
		Node();
		Node(E);
		Node(E, Node<E>*);
		~Node();

		void setData(E);
		void setNext(Node<E>*);

		E getData();
		Node<E>* getNext();

private:
		E data;
		Node<E>* next;
};

template <class E>
Node<E>::Node(){
	next = 0;
}

template <class E>
Node<E>::Node(E _data){
	next = 0;
	data = _data;
}

template <class E>
Node<E>::Node(E _data, Node* _next){
	data = _data;
	next = _next;
}

template <class E>
Node<E>::~Node(){
	
}

template <class E>
void Node<E>::setData(E _data){
	data = _data;
}

template <class E>
void Node<E>::setNext(Node* _next){
	next = _next;
}

template <class E>
E Node<E>::getData(){
	return data;
}

template <class E>
Node<E>* Node<E>::getNext(){
	return next;
}
#endif