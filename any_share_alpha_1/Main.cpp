#include "includer_cpp.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace std;

void addCalc(const boost::system::error_code& e, boost::asio::ip::tcp::iostream& s, as::addServer* p){
	if(e)
		return ;
	int x, y;
	s >> x >> y;
	s << x+y << "\r\n";
	s.close();
	p->start();
};

int main(){
	boost::asio::io_service io;
	as::addServer ads(io, 10101, addCalc);
	ads.start();
	io.run();

	return 0;
}
