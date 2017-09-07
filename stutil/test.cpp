#include <stutil/debug.h>
#include <stutil/events.h>
#include <iostream>
#include <unordered_set>
#include <fstream>


using namespace STUtil;

void testDebugger();
void testEvents();

int main() {
	// testDebugger();
	testEvents();

	return 0;
}

void testDebugger() {
	std::ofstream file( "debug.log" );
	file << "Opening file for debugging" << std::endl;

	std::cout << "============================================================" << std::endl;
	std::cout << "\tTesting Debug System" << std::endl;
	std::cout << "============================================================" << std::endl;
	std::cout << std::endl;


	Debug::log( "Logging to default channel" );

	Debug::addChannel( "Test" );
	Debug::channel( "Test" ).log( "Logging to custom channel Test using default output" );

	Debug::channel( "Test" ).mute();
	Debug::channel( "Test" ).log( "Muting channel Test" );

	Debug::channel( "Test" ).unmute();
	Debug::channel( "Test" ).log( "Unmuting custom channel Test" );

	Debug::channel( "blah" ).log( "Logging to unininitialized channel" );

	Debug::addChannel( "Test 2", file );
	Debug::channel( "Test 2" ).log( "Logging to custom channel Test using custom output" );

	Debug::channel( "Test" ).log( "Changing default output to file debug.log" );
	Debug::setDefault( file );
	Debug::log( "Testing default channel logging to file" );
	Debug::channel( "Test" ).log( "Testing default channel logging to file" );


}

class TestEvent : public Event<TestEvent> {};
class TestEvent2 : public Event<TestEvent2> {};
class FakeTestEvent : public Event<FakeTestEvent> {};

class TestListener : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::ID() )
			Debug::log( "TestEvent Happened in TestListener" );
		else if( event == TestEvent2::ID() )
			Debug::log( "TestEvent2 Happened in TestListener" );
	}
};

class TestListener2 : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::ID() )
			Debug::log( "TestEvent Happened in TestListener2" );
		else if( event == TestEvent2::ID() )
			Debug::log( "TestEvent2 Happened in TestListener2" );
	}
};

void testEvents() {
	Dispatcher* dispatch = new Dispatcher();
	TestListener* test = new TestListener();
	TestListener2* test2 = new TestListener2();

	std::cout << "============================================================" << std::endl;
	std::cout << "\tTesting Event System" << std::endl;
	std::cout << "============================================================" << std::endl;
	std::cout << std::endl;

	dispatch->addListener( TestEvent::ID(), test );
	dispatch->addListener( TestEvent::ID(), test2 );
	dispatch->addListener( TestEvent2::ID(), test2 );
	dispatch->addListener( TestEvent2::ID(), test );

	dispatch->dispatch( TestEvent::ID() );
	dispatch->dispatch( TestEvent2::ID() );
	dispatch->removeListener( TestEvent::ID(), test2 );
	dispatch->dispatch( TestEvent::ID() );
	dispatch->dispatch( TestEvent2::ID() );
	dispatch->dispatch( FakeTestEvent::ID() );

	delete dispatch;
}
