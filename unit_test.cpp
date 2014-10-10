#include "util/datastructs/darray.h"
#include "util/datastructs/stack.h"
#include "util/datastructs/queue.h"
#include "util/debug.h"
/*#include "Dispatcher.h"
#include "SceneManager.h"*/

#include <assert.h>
#include <cstring>
#include <time.h>

using namespace std;

//SceneManager* SceneManager::_instance = 0;
Debug* Debug::_instance = 0;

void testDArray(){
	DArray<int> arr;
	int i,j;
	unsigned int a, b;
	cout<<"\n==== DArray ====\n"<<endl;
	a = arr.allocated();
	for(b = 0; b <= a+10; b++){
		j = rand();
		if(!arr.add(j)) cout<< "[FAILED] Adding to array and retrieving"<<endl;
		if(arr.get(b) != j) cout<< "[FAILED] Adding to array and retrieving"<<endl;
		if(arr.length() != b+1) cout<<"[FAILED] Array length"<<endl;
	}
	cout<<"[PASSED] Adding to array and retrieving"<<endl;
	if(arr.allocated() <= a) cout<<"[FAILED] Expanding Array"<<endl;
	else cout<<"[PASSED] Expanding array"<<endl;

	i = arr.get(0);
	j = arr.get(-1);
	arr.swap(0, -1);
	if(i != arr.get(-1) || j != arr.get(0)) cout<<"[FAILED] Swapping elements"<<endl;
	else cout<<"[PASSED] Swapping elements"<<endl;

	arr.insert(-1, 5);
	if(arr.get(5) != -1) cout<<"[FAILED] Inserting"<<endl;
	else cout<<"[PASSED] Inserting"<<endl;

	i = arr.get(3);
	j = arr.get(4);

	arr.toFront(3);
	if(arr.get(0) == i && arr.get(4) == j) cout<<"[PASSED] Moving to front"<<endl;
	else cout<<"[FAILED] Moving to front"<<endl;

}

void testStack(){
	Stack<int> s;

	cout<<"\n==== Stack ====\n"<<endl;

	if(!s.push(1) || !s.push(2) || !s.push(3)) cout<<"[FAILED] Pushing to stack"<<endl;
	else cout<<"[PASSED] Pushing to stack"<<endl;

	if(s.size() != 3) cout<<"[FAILED] Checking size"<<endl;
	else cout<<"[PASSED] Checking Size"<<endl;

	if(s.peek() != 3) cout<<"[FAILED] Peeking"<<endl;
	else cout<<"[PASSED] Peeking"<<endl;

	if(s.pop() != 3 || s.pop() != 2 || s.pop() != 1) cout<<"[FAILED] Popping from stack"<<endl;
	else cout<<"[PASSED] Popping from stack"<<endl;

	if(s.size() != 0) cout<<"[FAILED] Checking size"<<endl;
	else cout<<"[PASSED] Checking Size"<<endl;
}

void testQueue(){
	Queue<int> q;

	cout<<"\n==== Queue ====\n"<<endl;

	if(!q.empty()) cout<<"[FAILED] Empty Checking"<<endl;
	else cout<<"[PASSED] Empty Checking"<<endl;

	q.queue(1);
	q.queue(2);
	q.queue(3);
	q.queue(4);

	if(q.size() != 4) cout<<"[FAILED] Queuing and Checking Size"<<endl;
	else cout<<"[PASSED] Queuing and Checking Size"<<endl;

	if(q.dequeue() != 1 || q.dequeue() != 2 || q.dequeue() != 3 || q.dequeue() != 4) cout<<"[FAILED] DeQueueing Objects"<<endl;
	else cout<<"[PASSED] DeQueueing Objects"<<endl;

	if(q.size() != 0 || !q.empty()) cout<<"[FAILED] Checking Size"<<endl;
	else cout<<"[PASSED] Checking Size"<<endl;
}

/*class dispatchTester{
	Dispatcher d;
};

void testDispatcher(){

}*/

int main(int argc, char const *argv[]){

	srand(time(0));

	//testDispatcher();

	testDArray();
	testStack();
	testQueue();

	return 0;
}
