#include "includer_std.h"
#include "network.h"

namespace as{
	namespace helper{
		void recvChat(const boost::system::error_code& e, std::iostream& s, as::addServer* ser, as::addSession *ses){
			if(e)
				return ;
			std::string str;
			s >> str;
			s << "echo : " << str;
		};
	}
	class chat{
	private:
		boost::asio::ip::tcp::iostream s;
		addServer *as_p;
		boost::asio::io_service io;
	public:
		chat(std::string to, std::string port){
			s.connect(to, port);
			//handler_t ht = &(chat::recvChat);
			as_p = new addServer(io, 20202, helper::recvChat);
		};
	};
}
