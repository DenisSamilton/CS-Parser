#ifndef _CLI_STRING_CONVERTER_
#define _CLI_STRING_CONVERTER_
#include <string>
using namespace System;

class SyStrToCString{
	public:
	void StringToStlWString( System::String const^ s, std::wstring& os );
	System::String^ StlWStringToString( std::wstring const& os );
	System::String^ WPtrToString( wchar_t const* pData, int length );

	//void Utf8ToStlWString( char const* pUtfString, std::wstring& stlString )
	//{
	//	//wchar_t* pString;
	//	MAKE_WIDEPTR_FROMUTF8( pString, pUtfString );
	//	stlString = pString;
	//}

	//void Utf8ToStlWStringN( char const* pUtfString, std::wstring& stlString, ULONG length )
	//{
	//	//wchar_t* pString;
	//	MAKE_WIDEPTR_FROMUTF8N( pString, pUtfString, length );
	//	stlString = pString;
	//}
};

#endif //_CLI_STRING_CONVERTER_