#include <iostream>
#include <time.h>

#include "Debug.h"
#include "SceneManager.h"

SceneManager* SceneManager::_instance = 0;
Debug* Debug::_instance = 0;

using namespace std;

int main(int argc, char const *argv[]){
	float startTime = time(0);
	float cTime, lastTime;

	for(cTime = time(0), lastTime = cTime; cTime - startTime < 30; cTime = time(0), lastTime = cTime){
		SceneManager::instance()->tick(cTime- lastTime);
	}


	return 0;
}
