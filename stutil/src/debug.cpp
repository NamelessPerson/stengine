#include <stutil/debug.h>

namespace STUtil {

	namespace {
		DebugChannel _log( "LOG" );
		DebugChannel _warn( "WARN" );
		DebugChannel _err( "ERR" );
	}

	//Debug Extern Definitions
	std::ostream* DebugChannel::defaultOutput 	= &std::cout;
	DebugChannel& Debug::log 				= _log;
	DebugChannel& Debug::warn 				= _warn;
	DebugChannel& Debug::err 				= _err;

	/*
	------------------------------------------------------------
		DebugChannel Class Methods
	------------------------------------------------------------
	*/
	DebugChannel::DebugChannel( std::string channelName, std::ostream& os ) : name( channelName ) {
		output = &os;
	}

	DebugChannel::DebugChannel( std::string channelName ) : name( channelName ) {
		output = NULL;
	}

	DebugChannel& DebugChannel::operator<<( std::ostream & ( *function )( std::ostream& ) ) {
		if(!muted)
			function( output == NULL ? *DebugChannel::defaultOutput : *output );
		return *this;
	}

	std::ostream& operator<<( std::ostream& os, const DebugChannel& channel ) {
		os << "{ name: " << channel.name << ", ";
		os << "output: " << ( channel.output == NULL ? "Default" : "Custom" ) << ", ";
		os << "muted: " << ( channel.muted ? "true" : "false" ) << "}" ;
		return os;
	}
}