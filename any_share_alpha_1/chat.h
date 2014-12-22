#ifndef __chat_h__
#define __chat_h__
#include "includer_std.h"
#include "network.h"

namespace as{
	namespace helper{
		static bool recvChat2(const boost::system::error_code& e, std::iostream& s, as::addServer* ser, as::addSession *ses){
			if(e)
				return false;
			std::string str;
			s >> str;
			s << "echo : " << str << std::endl;
			std::cout << "receive : " << str << std::endl;
			if(str=="exit"){
				delete ses;
				return false;
			}
			return true;
		};
	}
	class chat{
	private:
		boost::asio::ip::tcp::iostream s;
		addServer *as_p;
		boost::asio::io_service &io;
		std::vector<packet<std::string>> log;

	public:
		typedef packet<std::string> chat_t;
		chat(io_service &io, std::string to, std::string recvPort, unsigned short sendPort) : io(io){
			//s.connect(to, recvPort);
			//handler_t ht = &(chat::recvChat);
			//handler_t ht = helper::recvChat2;
			as_p = new addServer(io, sendPort, as::helper::recvChat2);
			io.run();
		};
	};
}
#endif
