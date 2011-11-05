/*
 * Copyright (c) 2011, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef ZS_LOGGER_HPP
#define ZS_LOGGER_HPP

#include <iostream>
#include <sstream>

namespace websocketpp {
namespace log {

namespace alog_level {
	typedef uint16_t value;
	
	static const value OFF = 0x0;
	
	// A single line on connect with connecting ip, websocket version, 
	// request resource, user agent, and the response code.
	static const value CONNECT = 0x1;
	// A single line on disconnect with wasClean status and local and remote
	// close codes and reasons.
	static const value DISCONNECT = 0x2;
	// A single line on incoming and outgoing control messages.
	static const value CONTROL = 0x4;
	// A single line on incoming and outgoing frames with full frame headers
	static const value FRAME_HEADER = 0x10;
	// Adds payloads to frame logs. Note these can be long!
	static const value FRAME_PAYLOAD = 0x20;
	// A single line on incoming and outgoing messages with metadata about type,
	// length, etc
	static const value MESSAGE_HEADER = 0x40;
	// Adds payloads to message logs. Note these can be long!
	static const value MESSAGE_PAYLOAD = 0x80;
	
	static const value ALL = 0xFFFF;
}	

namespace elog_level {
	typedef uint16_t value;
	
	static const value OFF = 0x0;
	
	static const value DEBUG = 0x1;
	static const value INFO = 0x2;
	static const value WARN = 0x4;
	static const value ERROR = 0x10;
	static const value FATAL = 0x20;
	
	static const value ALL = 0xFFFF;
}

template <typename level_type>
class logger {
public:
	

	//template <typename T>
	//logger& operator<<(T a);
	
	template <typename T>
	logger<level_type>& operator<<(T a) {
		if (test_level(m_write_level)) {
			oss << a;
		}
		return *this;
	}
	
	logger<level_type>& operator<<(logger<level_type>& (*f)(logger<level_type>& out)) {
		return f(*this);
	}
	
	/*
	logger& operator<<(endl) {
		std::cout << "fff" << oss.str() << std::endl;
		oss.str("");
		
		return *this;
	}*/
	
	bool test_level(level_type l) {
		return (m_level & l) != 0;
	}
	
	void set_level(level_type l) {
		m_level |= l;
	}
	
	void unset_level(level_type l) {
		m_level &= ~l;
	}
	
	logger<level_type>& print() {
		if (test_level(m_write_level)) {
			std::cout << "[timestamp] " << oss.str() << std::endl;
			oss.str("");
		}
		
		return *this;
	}
	
	logger<level_type>& at(level_type l) {
		m_write_level = l;
		return *this;
	}
private:
	std::ostringstream oss;
	level_type m_write_level;
	level_type m_level;
};

template <typename level_type>
logger<level_type>& endl(logger<level_type>& out)
{
	return out.print();
}

	
	
}
}

#endif // ZS_LOGGER_HPP
