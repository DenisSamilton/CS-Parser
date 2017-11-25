#include "stdafx.h"
#include <msclr\marshal_cppstd.h>
#include "CLIStringConverter.h"

using namespace System;
using namespace System::Runtime::InteropServices;
//using namespace Runtime::InteropServices;
//using namespace msclr::interop;

inline void SyStrToCString::StringToStlWString( System::String const ^ s, std::wstring & os )
{
	String^ string = const_cast<String^>(s);
	const wchar_t* chars = reinterpret_cast<const wchar_t*>((Marshal::StringToHGlobalUni( string )).ToPointer());
	os = chars;
	Marshal::FreeHGlobal( IntPtr( (void*)chars ) );

}

inline System::String ^ SyStrToCString::StlWStringToString( std::wstring const & os )
{
	String^ str = gcnew String( os.c_str() );
	//String^ str = gcnew String("");
	return str;
}

inline System::String ^ SyStrToCString::WPtrToString( wchar_t const * pData, int length )
{
	if( length == 0 )
	{
		//use null termination
		length = wcslen( pData );
		if( length == 0 )
		{
			System::String^ ret = "";
			return ret;
		}
	}

	System::IntPtr bfr = System::IntPtr( const_cast<wchar_t*>(pData) );
	System::String^ ret = System::Runtime::InteropServices::Marshal::PtrToStringUni( bfr, length );
	return ret;
}
