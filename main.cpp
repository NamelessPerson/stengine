#include <iostream>
#include "Debug.h"

using namespace std;

int main(int argc, char const *argv[]){

	string s;
	cout<<"Hello World!"<<endl;
	cin>>s;
	cout<<"Hello "<<s<<endl;

	DEBUG_LOG(0, "It works!");
	return 0;
}
