#include "DArray.h"

#include <assert.h>

using namespace std;

int main(int argc, char const *argv[]){
	DArray<int> arr(2);
	arr.add(5);
	arr.add(7);
	arr.add(8);
	arr.insert(22, 1);
	arr.print();
	/*int* arr = (int*)malloc(6*sizeof(int));
	int i;

	arr[0] = 4;
	arr[1] = 7;
	arr[3] = 9;
	arr[4] = 10;
	arr[5] = 22;

	for(i = 0; i < 6; i++)
		cout<<arr[i]<<", ";
	cout<<endl;

	arr = (int*)realloc(arr, 7*sizeof(int));
	for(i = 0; i < 7; i++)
		cout<<arr[i]<<", ";
	cout<<endl;

	memmove(arr+1, arr, 6*sizeof(int*));
	for(i = 0; i < 7; i++)
		cout<<arr[i]<<", ";
	cout<<endl;/**/
	return 0;
}