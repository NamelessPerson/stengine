#ifndef _DARRAY_H_
#define _DARRAY_H_

#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

template<class E>
class DArray{
public:
	DArray(unsigned int);
	~DArray();

	unsigned int length();
	unsigned int allocated();

	bool swap(unsigned int, unsigned int);
	bool insert(E, unsigned int);
	bool toFront(unsigned int);
	bool add(E);

	E remove(unsigned int);
	E get(unsigned int);

	void print();

private:
	E** elements;

	unsigned int _allocated;
	unsigned int _length;

	unsigned int resize();
};

template<class E>
DArray<E>::DArray(unsigned int size = 64){
	_length = 0;
	_allocated = size;
	elements = (E**)malloc(size*sizeof(E*));
}

template<class E>
DArray<E>::~DArray(){
	int i;

	for(i = 0; i < _length; i++)
		delete [] elements[i];
	free(elements);
}

template<class E>
unsigned int DArray<E>::length(){
	return _length;
}

template<class E>
unsigned int DArray<E>::allocated(){
	return _allocated;
}

template<class E>
bool DArray<E>::swap(unsigned int i, unsigned int j){
	if(i == -1) i = length - 1;
	if(j == -1) j = length - 1;
	if(i >= length || j >= length) return false;

	E* temp = elements[i];
	elements[i] = elements[j];
	elements[j] = temp;
	return true;
}

template<class E>
bool DArray<E>::insert(E item, unsigned int index){
	if(index == -1) index = _length;
	if(index > _length) return false;
	if(_length == _allocated && !resize()) return false;

	if(index != _length - 1)memmove(elements+index+1, elements+index, (_length-index)*sizeof(E*));
	elements[index] = new E;
	*elements[index] = item;
	_length ++;
	return true;
}

template<class E>
bool DArray<E>::toFront(unsigned int index){
	if(index == -1) index = _length-1;
	if(index >= _length) return false;
	
	E* temp = elements[index];
	memmove(elements+1, elements, index*sizeof(E*));
	elements[0] = temp;
	return true;
}

template<class E>
bool DArray<E>::add(E item){
	if(insert(item, -1)) return true;
	return false;
}

template<class E>
E DArray<E>::remove(unsigned int index){
	if(index == -1) index = _length-1;
	if(index >= _length || _length == 0) return 0;

	E temp = *elements[index];
	delete elements[index];
	memmove(elements+index, elements+index+1, (_length - index -1)*sizeof(E*));
	_length--;

	return temp;
}

template<class E>
E DArray<E>::get(unsigned int index){
	if(index >= _length) return 0;
	return *elements[index];
}

template<class E>
void DArray<E>::print(){
	int i;

	for(i = 0; i < _length; i++)
		cout<<i<<" - "<<*elements[i]<< endl;
}

template<class E>
unsigned int DArray<E>::resize(){
	_allocated += 32;
	elements = (E**)realloc(elements, (_allocated)*sizeof(E*));
	return _allocated;
}

#endif