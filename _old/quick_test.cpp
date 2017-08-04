#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	clock_t d = clock();
	clock_t last = d;
	while(true){
		d = clock();
		if(d-last > 0){
			cout<<d-last<<", "<<d<<endl;
			last = d;
		}
		
	}
	return 0;
}