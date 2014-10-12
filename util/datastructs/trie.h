#ifndef TRIE_H_
#define TRIE_H_

#include "../debug.h"
/*
============================================================
	TNode

Node class for the Trie which stores pointers to the next
children and the data located at that key.
============================================================
*/
template <class E>
class TNode{
public:
	TNode();
	~TNode();
	TNode<E>** children;
	E data;
};

/*
==============================================
	TNode()

Default constructor which instantiates 26 children
==============================================
*/
template <class E>
TNode<E>::TNode(){
	children = new TNode<E>*[26];
}

/*
============================================================
	Trie

Class for a Trie HashMap. Accepts keys of A-Z case insensitive.
Undefined behavior for non-accepted keys.
============================================================
*/
template <class E>
class Trie{
public:
	Trie();
	E get(const string& key);
	void add(string key, E data);
private:
	TNode<E>* head;
	int getTrieIndex(char c);
};

/*
==============================================
	Trie()

Default constructor. Instantiates head.
==============================================
*/
template <class E>
Trie<E>::Trie(){
	head = new TNode<E>();
}

/*
==============================================
getTrieIndex()

Utility method for converting an ASCII character 
to an index. For invalid charaters it returns 0(A)
and Logs an error.
==============================================
*/
template <class E>
int Trie<E>::getTrieIndex(char c){
	DEBUG_LOG(Debug::DATASTRUCTS, "Trie - getting index of " + to_string(c));
	if(c < 65 || c >122 || (c > 90 && c < 97)){
		DEBUG_ERR(Debug::DATASTRUCTS, "Ivalid Trie key character " + to_string(c));
		return 0;
	}
	//Captial
	else if(c < 97) return c - 65;
	//Lowercase
	else return c - 97;

}

/*
==============================================
	get(string key)

Returns the value at the given string
WARNING - undefined for unaccepted keys and
non-added strings
==============================================
*/
template <class E>
E Trie<E>::get(const string& key){
	TNode<E>* curr = head;
	char c;
	int i;

	DEBUG_LOG(Debug::DATASTRUCTS, "Getting key " + key);

	for(i = 0, c = key[i]; i < key.length(); i++, c = key[i]){
		curr = curr->children[getTrieIndex(c)];
		if(!curr) DEBUG_ERR(Debug::DATASTRUCTS, "Trie - key not initialized at "+ to_string(getTrieIndex(c)));
	}
	return curr->data;
}

/*
==============================================
	add(string key, E data)

Adds/overwrites key with data.
WARNING - undefined for unaccepted keys 
==============================================
*/
template <class E>
void Trie<E>::add(string key, E data){
	TNode<E>* curr = head;
	char c;
	int i,j;

	DEBUG_LOG(Debug::DATASTRUCTS, "Adding key " + key);

	for(i = 0, c = key[i]; i < key.length(); i++, c = key[i]){
		j = getTrieIndex(c);
		if(!curr->children[j]) curr->children[j] = new TNode<E>();
		curr = curr->children[getTrieIndex(c)];
	}
	curr->data = data;
}

#endif
