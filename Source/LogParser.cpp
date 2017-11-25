#include "stdafx.h"
#include "LogParser.h"
//#include <iostream>

Mys::Mys() 
{ 
	s = new wstring * [eventCount];
	for( size_t i = 0; i < eventCount; i++ )
		s[i] = new wstring[countStringInEvent];

	for( size_t i = 0; i < eventCount; i++ )
		for( size_t j = 0; j < countStringInEvent; j++ )
			s[i][j] = to_wstring(i) + L". Event number " + to_wstring(j);
}

void Mys::setFileName( wstring str )
{
	fileName = str;
}

wstring Mys::getFileName()
{
	
		if( ! fileName.empty() )
			return fileName;
		else throw gcnew System::ArgumentException( "Error: File Name is emty!");
}
