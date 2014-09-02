#include "DArray.h"

#include <assert.h>
#include <cstring>
#include <time.h>

using namespace std;

int main(int argc, char const *argv[]){
	
	int i, j;
	unsigned int a;

	DArray<int> arr;
	DArray<int> arr2(2);
	DArray<int> arr3(-12);
	DArray<string> arr4(-3);

	srand(time(0));

	assert(arr2.allocated() == 2 && "[FAILED] Initialization");
	assert(arr3.allocated() == -12 && "[FAILED] Initialization"); 
	assert(arr4.allocated() == -3 && "[FAILED] Initialization");
	cout<<"[PASSED] Initialization"<<endl;

	for(i = 0; i < 32; i ++){
		j = rand();
		assert(arr.add(j) && "[FAILED] Adding to array and retrieving");
		assert(arr.get(i) == j && "[FAILED] Adding to array and retrieving");
	}
	cout<<"[PASSED] Adding to array and retrieving"<<endl;

	a = arr2.allocated();
	for(i = 0; i <= a; i++){
		j = rand();
		arr2.add(j);
		assert(arr2.get(i) == j && "[FAILED] Expanding Array");
	}
	assert(arr2.allocated() > a && "[FAILED] Expanding Array");
	cout<<"[PASSED] Expanding Array"<<endl;

	

	return 0;
}