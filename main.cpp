//#include <stdio.h>
#include <string>
#include <iostream>
//#include <time.h>

/*#include "Debug.h"
#include "SceneManager.h"
#include "FixedGrid.h"

SceneManager* SceneManager::_instance = 0;
Debug* Debug::_instance = 0;*/

//using namespace std;

int main(){
	int x = 1;
	std::string g = "g";
	std::string s = std::to_string(x);
	s += g;
	std::cout << s << std::endl;
	/*clock_t start = clock();
	clock_t curr, last;

	SceneManager::instance()->setGraph(new FixedGrid());
	SceneManager::instance()->addTickable(new GridController());

	for(curr = clock(), last = curr; curr - start < 6000; last = curr, curr = clock()){
		SceneManager::instance()->tick(curr - last);
		//cout << "At" << (curr - start) << " - " << (curr - last) << endl;
	}*/
	

	return 0;
}
