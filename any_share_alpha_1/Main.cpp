#include "includer_cpp.h"

using namespace std;

void addCalc(const boost::system::error_code& e, std::iostream& s, as::addServer* ser, as::addSession *ses){
	if(e)
		return ;
	string str;
	s >> str;
	s << "echo : " << str;
};

int main(){
	boost::asio::io_service io;
	as::addServer ads(io, 10101, addCalc);
	ads.start();
	io.run();

	return 0;
}
