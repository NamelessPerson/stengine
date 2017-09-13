#include <stutil/debug.h>
#include <stutil/events.h>
#include <iostream>
#include <unordered_set>
#include <fstream>


using namespace STUtil;

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


	Debug::log << "Logging to default channel: " << std::endl; //std::endl;
	Debug::log.muted = true;
	Debug::log << "Logging to default channel while muted" << std::endl;
	Debug::log.muted = false;
	Debug::log << "Printing Channel: " << Debug::log << std::endl;

	DebugChannel test("Test");
	test << "Logging to custom channel Test using default output"  << std::endl;

	test.muted = true;
 	test << "Muting channel Test" << std::endl;
	test.muted = false;

	test << "Unmuting custom channel Test"  << std::endl;

	DebugChannel testFile("TestFile", file);
	testFile << "Logging to custom channel TestFile using custom output"  << std::endl;

	Debug::log << "Changing default output to file debug.log" << std::endl;
	DebugChannel::defaultOutput = &file;
	Debug::log << "Testing default channel logging to file" << std::endl;
	DebugChannel::defaultOutput = &std::cout;
}

class TestEvent : public Event<TestEvent> {};
class TestEvent2 : public Event<TestEvent2> {};
class FakeTestEvent : public Event<FakeTestEvent> {};

class TestListener : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::ID() )
			Debug::log << "TestEvent Happened in TestListener\n";
		else if( event == TestEvent2::ID() )
			Debug::log << "TestEvent2 Happened in TestListener\n";
	}
};

class TestListener2 : public IEventListener {
public:
	void onEvent( EventID event ) {
		if( event == TestEvent::ID() )
			Debug::log << "TestEvent Happened in TestListener2\n";
		else if( event == TestEvent2::ID() )
			Debug::log << "TestEvent2 Happened in TestListener2\n";
	}
};

void testEvents() {
	Dispatcher* dispatch = new Dispatcher();
	TestListener* test = new TestListener();
	TestListener2* test2 = new TestListener2();

	Debug::log << "============================================================" << std::endl;
	Debug::log << "\tTesting Event System" << std::endl;
	Debug::log << "============================================================" << std::endl;
	Debug::log << std::endl;

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
