#include <stutil/util.h>
#include <iostream>
#include <unordered_map>
#include "fstream"

void testDebugger() {
	std::ofstream file( "debug.log" );
	file << "Opening file for debugging" << std::endl;

	Debug::log( "Logging to default channel" );

	Debug::addChannel( "Test" );
	Debug::channel( "Test" ).log( "Logging to custom channel Test using default output" );

	Debug::channel( "Test" ).mute();
	Debug::channel( "Test" ).log( "Muting channel Test" );

	Debug::channel( "Test" ).unmute();
	Debug::channel( "Test" ).log( "Unmuting custom channel Test" );

	Debug::channel("blah").log("Logging to unininitialized channel");

	Debug::addChannel( "Test 2", file );
	Debug::channel( "Test 2" ).log( "Logging to custom channel Test using custom output" );

	Debug::channel( "Test" ).log( "Changing default output to file debug.log" );
	Debug::setDefault( file );
	Debug::log( "Testing default channel logging to file" );
	Debug::channel( "Test" ).log( "Testing default channel logging to file" );


}

int main() {
	testDebugger();

	return 0;
}