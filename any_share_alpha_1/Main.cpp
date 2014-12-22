#include "includer_cpp.h"

using namespace std;

bool addCalc(const boost::system::error_code& e, std::iostream& s, as::addServer* ser, as::addSession *ses){
	if(e)
		return false;
	string str;
	s >> str;
	s << "echo : " << str << endl;
	cout << "receive : " << str << endl;
	if(str=="exit"){
		delete ses;
		return false;
	}
	return true;
};

int main(){
	boost::asio::io_service io;
	//as::addServer ads(io, 10101, addCalc);
	unsigned short p;
	cin >> p;
	if(p==10101){
		as::chat ch(io, "", "", p);
		io.run();
	}else{
		boost::asio::ip::tcp::iostream s;
		s.connect("localhost", "10101");
		string c[] = {"test", "str", "exit"};
		for(string str : c){
			s << str << "\r\n" << std::flush;
			string line;
			//while(getline(s, line))
			//	cout << line << endl;
			string buf;
			getline(s, buf);
			cout << buf << endl;
		}
	}
	return 0;
}
