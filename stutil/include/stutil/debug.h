#ifndef _STUTIL_DEBUG_H_
#define _STUTIL_DEBUG_H_

#include <string>
#include <iostream>
#include <unordered_map>

namespace STUtil {

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
		DebugChannel& operator<<( std::ostream & ( *function )( std::ostream& ) );
		friend std::ostream& operator<<( std::ostream& os, const DebugChannel& channel );

		static std::ostream* defaultOutput;

		const std::string 	name;
		std::ostream* 		output;
		bool				muted;
	};

	namespace Debug {
		extern DebugChannel& log;
		extern DebugChannel& warn;
		extern DebugChannel& err;
	};

	template<class T>
	DebugChannel& DebugChannel::operator<<( const T& t ) {
		if( !muted ) {
			std::ostream& out = ( output == NULL ? *DebugChannel::defaultOutput : *output );

			if( out.tellp() <= 0 )
				out << "[" << name << "] ";

			out << t;
		}

		return *this;
	}


}

#endif
