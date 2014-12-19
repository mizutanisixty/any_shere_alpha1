#ifndef __network_h__
#define __network_h__
#include "includer_std.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace as{
	using namespace boost::asio;
	using ip::tcp;
	using boost::system::error_code;
	class addSession{
		friend class addServer;
		tcp::socket sok;
		boost::asio::streambuf buf;
		addSession(io_service &io) : sok(io){
		};
		void start(){
			async_read_until(sok, buf, '\n',
				boost::bind(&addSession::read_ok, this, _1, _2));
		};
		void read_ok(const error_code &e, size_t siz){
			if(e){
				delete this;
				return ;
			}
			std::iostream s(&buf);
			int x, y;
			s >> x >> y;
			s << x+y << std::endl;
			async_write(sok, buf, boost::bind(&addSession::write_ok, this, _1, _2));
		};
		void write_ok(const error_code &e, size_t siz){
			if(e){
				delete this;
				return ;
			}
			start();
		};
	};
	class addServer{
	private:
		typedef void (*handler_t)(const error_code&, tcp::iostream&, addServer*);
		io_service& io;
		//tcp::iostream s;
		tcp::acceptor acc;
		handler_t cHandler;
		addSession *cur_session;

		void handler(const error_code &e){
			if(e){
				delete cur_session;
				return ;
			}
			cur_session->start();
			start();
		};
	public:
		void start(){
			//acceptŠ®—¹ŽŸ‘æthis->handler()‚ðŒÄ‚Ño‚·
			//acc.async_accept(*s.rdbuf(), boost::bind(&addServer::handler, this, _1));
			cur_session = new addSession(io);
			acc.async_accept(cur_session->sok,
				boost::bind(&addServer::handler, this, _1));
		};
		addServer(io_service &io, unsigned short port, handler_t handler) : io(io), acc(io, tcp::endpoint(ip::address_v4(), port)){
				cHandler = handler;
		};
		
	};

}
#endif
