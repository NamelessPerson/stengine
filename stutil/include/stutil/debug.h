#ifndef _STUTIL_DEBUG_H_
#define _STUTIL_DEBUG_H_

#include <string>
#include <iostream>
#include <unordered_map>

namespace STUtil {

	/*
	============================================================
		Debug

	This is a singleton logger class for debugging
	However it is used like a static class and instance() is private

	Users should use the class as such:

		Debug::log("message") 						// Log to default channel
		Debug::channel("channel").log("message")	// Log to channel of choice

	By default this class is instantiated with the following channels:

		DEBUGGER	- a channel which should by used only by the debugger
		UNKNOWN		- a channel used when logging to an unintialized channel
		LOG 		- the default logging channel

	Channel names are currently case sensitive but that should change
	Also there is currently no way to remove channels since there shouldn't be a need

	============================================================
	*/
	class Debug {
	public:
		/*
		------------------------------------------------------------
			Channel Class Definition

		Can only be constructed by the Debug class
		Used to log information to an output stream
		------------------------------------------------------------
		*/
		class Channel {
		public:
			template<typename T>
			void 		log( const T message );
			void		mute();
			void		unmute();

		private:
			friend Debug;
			Channel( const std::string name, std::ostream* output );

			static std::ostream* defaultOutput;
			std::string 		_name;
			std::ostream* 		_output;
			bool				muted;
		};

		/*
		------------------------------------------------------------
			Singleton overides
		------------------------------------------------------------
		*/
		Debug( const Debug& ) 				= delete;
		Debug& 	operator=( const Debug& )	= delete;

		/*
		------------------------------------------------------------
			Useful Methods

		addChannel		- Adds a channel which can be written to.
						  If no output is given, default output is used
						  Returns false if channel already exists.

		setDefault		- Changes the default channel.
						  Returns false if channel doesn't exist.

		channel			- Retrieves a channel to log to.

		log				- Writes a message to the default channel.
		------------------------------------------------------------
		*/
		template<typename T>
		static void		log( const T messsage );
		static bool		addChannel( const std::string channelName );
		static bool		addChannel( const std::string channelName, std::ostream& output );
		static void		setDefault( std::ostream& output );
		static Channel&	channel( const std::string channelName );

	private:
		Debug();

		static Debug* 	_instance;
		Channel* 		defaultChannel;
		std::unordered_map<std::string, Channel*>*	channels;

		static Debug& 	instance();
		Channel& 		operator[]( const std::string& );
	};

	/*
	------------------------------------------------------------
		Templated Methods
	------------------------------------------------------------
	*/
	template<typename T>
	void Debug::log( const T message ) {
		Debug::instance().defaultChannel->log( message );
	}

	template<typename T>
	void Debug::Channel::log( const T message ) {
		if( !muted ) {
			if( _output )
				*_output << "[" << _name << "]\t" << message << std::endl;
			else
				*defaultOutput << "[" << _name << "]\t" << message << std::endl;
		}
	}

}

#endif
