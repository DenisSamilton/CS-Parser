#ifndef _LOG_PARCER_
#define _LOG_PARCER_

#include <string>
#include <list>
#include <vector>
using namespace std;

class Mys{

	wstring fileName;

	public:
	size_t eventCount = 10,
				 countStringInEvent = 3;
	wstring **s = nullptr;
	
	public:
	Mys();
	void setFileName( wstring str );
	wstring getFileName();
};

#endif //_LOG_PARCER_