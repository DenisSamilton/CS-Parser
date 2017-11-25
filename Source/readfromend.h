#include "stdafx.h"
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include <cstdlib>

namespace logparsercs
{
	class ReadFromEnd{
		public:
		int error = 0;
		long long curpos = 0;

		ReadFromEnd( std::wstring path, std::wstring tmpPath, long long curPos, size_t maxLineToRead, int maxLineLength )
		{
			std::wifstream rStream( path );
			if( !rStream.is_open() )
			{
				//std::wcout <<L"err: path";
				System::Windows::Forms::MessageBox::Show( "File \"" + gcnew System::String( path.c_str() ) + "\" opening failed", "Error" );
				error = 1;
				curpos = curPos;
				return;
			}

			std::wofstream wStream( tmpPath, std::ios::out | std::ios::trunc );
			if( !wStream.is_open() )
			{
				//std::wcout << L"err: tmpPath";
				System::Windows::Forms::MessageBox::Show( "File \"" + gcnew System::String( tmpPath.c_str() ) + "\" opening failed", "Error" );
				error = 2;
				curpos = curPos;
				rStream.close(); return;
			}

			wchar_t *buf = new wchar_t[maxLineLength];

			//curPos -= 1;
			rStream.seekg( curPos, rStream.beg );

			for( size_t i = 0; i < maxLineToRead; i++ )
			{
				if( !rStream.good() )
				{ // Проверяем, что именно произошло: кончился файл или это ошибка чтения
					if( rStream.eof() ) //Если файл закончился
						break;
					else
					{	//Если при чтении произошла ошибка
						error = 3;
						curpos = curPos;
						//std::wcout << L"! good(): while path";
						//System::Windows::Forms::MessageBox::Show( "File \"" + gcnew System::String( path.c_str() ) + "\" opening failed", "Error" );
						delete[] buf;
						rStream.close();
						wStream.close();
					}
				}

				rStream.getline( buf, maxLineLength );

				//std::wcout <<buf <<std::endl;
				wStream << buf << std::endl;

				//System::Windows::Forms::MessageBox::Show( "writed to tmp\"" + gcnew System::String( buf ) + "\"" );
			}

			if( rStream.tellg() > curPos )
				curpos = rStream.tellg();
			else
				curpos = curPos;

			delete[] buf;
			rStream.close();
			wStream.close();
		}

		static long long GetLastPosition( std::wstring &path )
		{
			bool err = true;
			std::wifstream rStream;

			while( err )
			{
				rStream.open( path, std::ios::in );

				if( rStream.is_open() )
					err = false; //Если удалось открыть файл, выходим из цикла
				else
					;//std::wcout <<L"err: path";
					//System::Windows::Forms::MessageBox::Show( "File \"" + gcnew System::String( path.c_str() ) + "\" opening failed", "Error" );
			}

			rStream.seekg( 0, rStream.end );
			long long lastPos = rStream.tellg();

			rStream.close();
			return lastPos;
		}

	};
}