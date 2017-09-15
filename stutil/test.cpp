#include <stutil/debug.h>
#include <stutil/events.h>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <fstream>


using namespace stutil;

void testDebugger();
void testNewDebugger();
void testEvents();

int main() {
	testDebugger();
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


	debug::log << "Logging to default channel: " << debug::endl;
	debug::log.muted = true;
	debug::log << "Logging to default channel while muted" << debug::endl;
	debug::log.muted = false;
	debug::log << "Printing Channel: " << debug::log << debug::endl;

	DebugChannel test("Test");
	test << "Logging to custom channel Test using default output"  << debug::endl;

	test.muted = true;
 	test << "Muting channel Test" << debug::endl;
	test.muted = false;

	test << "Unmuting custom channel Test"  << debug::endl;

	DebugChannel testFile("TestFile", file);
	testFile << "Logging to custom channel TestFile using custom output"  << debug::endl;

	debug::log << "Changing default output to file debug.log" << debug::endl;
	DebugChannel::defaultOutput = &file;
	debug::log << "Testing default channel logging to file" << debug::endl;
	DebugChannel::defaultOutput = &std::cout;
}

class TestEvent : public Event<TestEvent> {};
class TestEvent2 : public Event<TestEvent2> {};
class FakeTestEvent : public Event<FakeTestEvent> {};

class TestListener : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::ID() )
			debug::log << "TestEvent Happened in TestListener" << debug::endl;
		else if( event == TestEvent2::ID() )
			debug::log << "TestEvent2 Happened in TestListener" << debug::endl;
	}
};

class TestListener2 : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::ID() )
			debug::log << "TestEvent Happened in TestListener2" << debug::endl;
		else if( event == TestEvent2::ID() )
			debug::log << "TestEvent2 Happened in TestListener2" << debug::endl;
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
