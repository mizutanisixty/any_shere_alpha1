#include "includer_cpp.h"

using namespace std;

void addCalc(const boost::system::error_code& e, std::iostream& s, as::addServer* ser, as::addSession *ses){
	if(e)
		return ;
	string str;
	s >> str;
	s << "echo : " << str << endl;
	cout << "echo : " << str << endl;
	if(str == "exit"){
		cout << "exit\n";
		//delete ses;
		//ˆê“I‚Éãè‚­‚¢‚­‚ªŒã‚©‚çƒGƒ‰[
	}
};

int main(){
	boost::asio::io_service io;
	as::addServer ads(io, 10101, addCalc);
	io.run();

	return 0;
}
