#pragma once
#ifndef _SERVICE_
#define _SERVICE_

#include <iomanip>
#include <string>
#include <sstream>

namespace logparsercs {

	struct Time {
		short day, month, year;
		short hours, min, sec, millisec;
	};

	inline int calcTimeDiff( const Time newer, const Time older )
	{
		return 24 * (365 * (newer.year - older.year) 
									+ 30 * (newer.month - older.month) 
									+ (newer.day - older.day)) 
									+ (newer.hours - older.hours);
	}

	template <typename T>
	void hexToDec(const std::wstring& hexValue, T& result)
	{
		std::wstringstream ss;
		ss << std::hex << hexValue;
		ss >> result;
	}
	
	template <typename T>
	void hexDmToDec(const std::wstring& hexValue, T& result)
	{
		hexToDec(hexValue, result);
		result = result & 127;
	}

}
#endif