#ifndef __struct__
#define __struct__

#include <string>

namespace as{
	struct MEMBER{
		unsigned long long int mid;
		std::string name;
	};

	template <class T> struct packet{
		MEMBER author;
		time_t time;
		T data;
	};
}

#endif
