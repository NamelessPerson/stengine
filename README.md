# Simple Terminal Engine

This repository is for a simple game engine, utilities, and example games which render in a linux terminal using ncurses. <br>
Originally this was for a game development class but I am now revamping it piece by piece. <br>
<!-- [SimpleINI Header](./include/simpleini/simpleini.h) is borrowed from Brodie Thiesfield and the original project can be found [here](https://github.com/brofield/simpleini). <br> -->
You can see the original code located in [\_old](./_old) but I would rather you look at the newer things <br>

## Usage
The stengine build system requires linux with `g++-7` and `libncurses-dev` installed <br>
In the future I will include a Visual Studio Solution for building on windows <br>
<br>
The build system can be used entirely from the root<br>
Currently the best way to run the new project is using:
```bash
make util test
make engine test
```
This will run the simple unit tests for the utilities library.

## Todo
Current planned action items before next version

- Settings Manager
- Input Manager
- Ncurses Rendering System
- Snake Example game

## Changelog

##### Sept 19
First pass at a rendering system.

##### Sept 14
More Debug system improvements. Now supports multiple buffered input using:
```cpp
debug::log << "This is a " << " good example " << debug::endl;
```

Which will output:
```
[LOG] This is a good example
```

##### Sept 13
All systems now using c++14 <br>
Huge improvements to [Debug](./stutil/include/stutil/debug.h) system. Now works similar to the standard output:
```cpp
Debug::log << "This is a " << " good example " << std::endl;
```
EDIT: This outputted `[LOG] This is a [LOG] good example`. This is fixed in the next recent update.
See the full demonstration in the [tests](./stutil/test.cpp)

##### Sept 8
Implemented super simple [SceneGraph](./stengine/include/stengine/fixedgrid.h) which uses a grid of vectors to organize data <br>
This graph only supports point sized elements and will be replaced in the future <br>

##### Sept 6
Upgraded to `g++-7`<br>
Some initial setup for GameManager, GameObjects, and GameComponents. <br>
Most new code is not fully fleshed out and will soon change <br>

##### Aug 25
Moved everything into a namespace <br>
Finished first pass at an event system. See [events.h](./stutil/include/stutil/events.h) and [events.cpp](./stutil/src/events.cpp) <br>
You can see an example use in the [tests](./stutil/test.cpp) <br>
Possible later extension would be passing constructed Event objects to be able to include information about the event <br>

##### Aug 15
Finished the new and vastly improved Debug logging system. <br>
New system allows users to create custon channels with custom output locations to help manage debug messages <br>
See [debug.h](./stutil/include/stutil/debug.h) and [debug.cpp](./stutil/src/debug.cpp) or look at the [tests](./stutil/test.cpp) to see it being utilized.

##### Aug 9
Setup build system

##### Aug 4
Started revamp of project

## _old
The original code should still be buildable on a linux system using the makefile. <br>
The buildable version currently just has a Dwarf(D) moving across the screen
