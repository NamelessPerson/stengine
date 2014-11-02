#ifndef _DARRAY_H_
#define _DARRAY_H_

#include <cstdlib>
#include <iostream>
#include <cstring>
#include "../debug.h"

using namespace std;

/*
============================================================
	DArray

This Dynamic Array class is meant as a replacement for the
C++ standard vector. It poorly expands its capacity by 32 
when filled.
============================================================
*/
template<class E>
class DArray{
public:
	DArray();
	DArray(unsigned int);
	~DArray();

	unsigned int length();
	unsigned int allocated();

	bool swap(unsigned int, unsigned int);
	bool insert(E, unsigned int);
	bool toFront(unsigned int);
	bool add(E);

	E remove(unsigned int);
	bool remove(E);
	E get(unsigned int);

	void print();
private:

	E* elements;

	unsigned int _allocated;
	unsigned int _length;

	unsigned int resize();
};

/*
==============================================
DArray()

Default constructor. Will initialize the Array
to a size of 8 if not specified.
==============================================
*/
template<class E>
DArray<E>::DArray(){
	unsigned int size = 8;
	_length = 0;
	_allocated = size;
	elements = (E*)malloc(size*sizeof(E));
}

/*
==============================================
	DArray(unsigned int size)

Constructs a DArray with an initial size of size.
==============================================
*/
template<class E>
DArray<E>::DArray(unsigned int size){
	_length = 0;
	_allocated = size;
	elements = (E*)malloc(size*sizeof(E));
}

/*
==============================================
	~DArray()

Deconstructor.
==============================================
*/
template<class E>
DArray<E>::~DArray(){
	free(elements);
}

/*
==============================================
	unsigned int length()

Returns the current number of objects in the
array.
==============================================
*/
template<class E>
unsigned int DArray<E>::length(){
	return _length;
}

/*
==============================================
	unsigned int allocated()

Returns the current number of spaces allocated
in memory.
==============================================
*/
template<class E>
unsigned int DArray<E>::allocated(){
	return _allocated;
}

/*
==============================================
	bool swap(unsigned int i, unsigned int j)

Swaps the items at indices i and j. Will return
false if i or j are outside the scope of the
array.
==============================================
*/
template<class E>
bool DArray<E>::swap(unsigned int i, unsigned int j){
	if(i == j) return true;
	if(i == -1) i = _length - 1;
	if(j == -1) j = _length - 1;
	if(i >= _length || j >= _length) return false;

	E temp = elements[i];
	elements[i] = elements[j];
	elements[j] = temp;
	return true;
}

/*
==============================================
	bool insert(E item, unsigned int index)

Will insert item into the array at index. If an
index of -1 is inputted, it will place the item
at the end of the array instead. If index is
outside the scope of the array (and not -1), 
the function will return false.
==============================================
*/
template<class E>
bool DArray<E>::insert(E item, unsigned int index){
	if(index == -1) index = _length;
	if(index > _length) return false;
	if(_length == _allocated && !resize()) return false;

	if(index != _length) memmove(elements+index+1, elements+index, (_length-index)*sizeof(E));
	elements[index] = item;
	_length++;
	return true;
}

/*
==============================================
	bool toFront(unsigned int index)

Pushes the object at index to the front of the
array. -1 is treated as the index at the end of
the array. If index is outside the scope of the 
array (and not -1), the function will return false.
==============================================
*/
template<class E>
bool DArray<E>::toFront(unsigned int index){
	if(index == -1) index = _length-1;
	if(index >= _length) return false;
	
	E temp = elements[index];
	memmove(elements+1, elements, index*sizeof(E));
	elements[0] = temp;
	return true;
}

/*
==============================================
	add(E item)

Adds item to the array by calling insert.
==============================================
*/
template<class E>
bool DArray<E>::add(E item){
	return insert(item, -1);
}

/*
==============================================
	E remove(unsigned int index)

Removes an item from the array and shifts all
proceeding objects down.
==============================================
*/
template<class E>
E DArray<E>::remove(unsigned int index){
	if(index == -1) index = _length-1;

	E temp = elements[index];
	memmove(elements+index, elements+index+1, (_length - index -1)*sizeof(E));
	_length--;

	return temp;
}

/*
==============================================
	E remove(E item)

Removes an item from the array and shifts all
proceeding objects down. Undefined and logged
error if E is not in the array
==============================================
*/
template<class E>
bool DArray<E>::remove(E item){
	int index = 0;

	for(index = 0; index < _length; index++){
		//index will be where the item is in the array.
		if(elements[index] == item) break;
	}

	if(index >= _length){
		DEBUG_WARN(Debug::DATASTRUCTS, "Trying to remove non-existant element.");
		return false;
	}

	memmove(elements + index, elements + index + 1, (_length - index - 1)*sizeof(E));
	_length--;

	return true;
}

/*
==============================================
	E get(unsigned int index)

Returns the object at index.-1 is treated as the
index at the end of the array. If index is outside 
the scope of the array (and not -1), the function 
will return false.
==============================================
*/
template<class E>
E DArray<E>::get(unsigned int index){
	if(index == -1) index = _length-1;
	
	return elements[index];
}

/*
==============================================
	void print()

Helpful debugging method that prints the items
inside the array.
==============================================
*/
template<class E>
void DArray<E>::print(){
	int i;

	for(i = 0; i < _length; i++)
		cout<<i<<" - "<<elements[i]<< endl;
}

/*
==============================================
	unsigned int resize()

This method is called when the array fills up.
It uses realloc() to increase the memory block
by a factor of 32.
==============================================
*/
template<class E>
unsigned int DArray<E>::resize(){
	_allocated += 32;
	elements = (E*)realloc(elements, (_allocated)*sizeof(E));
	return _allocated;
}

#endif
