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
	std::cout << "Testing Debug System" << std::endl;
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
		if( event == TestEvent::StaticID() )
			Debug::log( "TestEvent Happened in TestListener" );
		else if( event == TestEvent2::StaticID() )
			Debug::log( "TestEvent2 Happened in TestListener" );
	}
};

class TestListener2 : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::StaticID() )
			Debug::log( "TestEvent Happened in TestListener2" );
		else if( event == TestEvent2::StaticID() )
			Debug::log( "TestEvent2 Happened in TestListener2" );
	}
};

void testEvents() {
	Dispatcher dispatch;
	TestListener* test = new TestListener();
	TestListener2* test2 = new TestListener2();

	std::cout << "============================================================" << std::endl;
	std::cout << "Testing Event System" << std::endl;
	std::cout << "============================================================" << std::endl;
	std::cout << std::endl;
	
	dispatch.addListener( TestEvent::StaticID(), test );
	dispatch.addListener( TestEvent::StaticID(), test2 );
	dispatch.addListener( TestEvent2::StaticID(), test2 );
	dispatch.addListener( TestEvent2::StaticID(), test );
	
	dispatch.dispatch( TestEvent::StaticID() );
	dispatch.dispatch( TestEvent2::StaticID() );
	dispatch.removeListener(TestEvent::StaticID(), test2);
	dispatch.dispatch( TestEvent::StaticID() );
	dispatch.dispatch( TestEvent2::StaticID() );
	dispatch.dispatch( FakeTestEvent::StaticID() );

}
