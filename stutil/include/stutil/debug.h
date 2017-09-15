#ifndef _STUTIL_DEBUG_H_
#define _STUTIL_DEBUG_H_

#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace stutil {

	/*
	============================================================

		DebugChannel
		
	This class provides a custom output mechanism using channels which can have
	unique outputs or use a default one. By default there are a
	============================================================
	*/
	struct DebugChannel {
		DebugChannel( const std::string channelName );
		DebugChannel( const std::string channelName, std::ostream& os );

		template<class T>
		DebugChannel& operator<<( const T& t );
		DebugChannel& operator<<( std::ostream& ( *function )( std::ostream& ) );
		DebugChannel& operator<<( DebugChannel& ( *function )( DebugChannel& ) );
		friend std::ostream& operator<<( std::ostream& os, const DebugChannel& channel );

		static std::ostream* defaultOutput;

		const std::string 	name;
		std::ostream* 		output;
		bool				muted;
		std::stringstream _buf;

	private:
	};

	namespace debug {
		extern DebugChannel& log;
		extern DebugChannel& warn;
		extern DebugChannel& err;
		DebugChannel& endl(DebugChannel&);
	};

	template<class T>
	DebugChannel& DebugChannel::operator<<( const T& t ) {
		if( !muted ) {
			_buf << t;
		}

		return *this;
	}


}

#endif
