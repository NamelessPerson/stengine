#include <stutil/debug.h>

namespace stutil {

	namespace {
		DebugChannel _log( "LOG" );
		DebugChannel _warn( "WARN" );
		DebugChannel _err( "ERR" );
	}

	//Debug Extern Definitions
	std::ostream* DebugChannel::defaultOutput 	= &std::cout;
	DebugChannel& debug::log 				= _log;
	DebugChannel& debug::warn 				= _warn;
	DebugChannel& debug::err 				= _err;

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
		if( !muted )
			function( _buf );

		return *this;
	}

	DebugChannel& DebugChannel::operator<<( DebugChannel & ( *function )( DebugChannel& ) ) {
		if( !muted )
			function( *this );

		return *this;
	}

	DebugChannel& debug::endl( DebugChannel& chan ) {
		std::ostream& out = ( chan.output == NULL ? *DebugChannel::defaultOutput : *(chan.output) );
		out << "[" << chan.name << "] " << chan._buf.str() << std::endl;
		chan._buf.str(std::string());

		return chan;
	}


	std::ostream& operator<<( std::ostream& os, const DebugChannel& channel ) {
		os << "{ name: " << channel.name << ", ";
		os << "output: " << ( channel.output == NULL ? "Default" : "Custom" ) << ", ";
		os << "muted: " << ( channel.muted ? "true" : "false" ) << "}" ;
		return os;
	}
}