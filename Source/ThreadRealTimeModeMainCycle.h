#include "stdafx.h"
#include "ThreadRealTime.h"

namespace logparsercs
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Threading;
	public ref class ThreadRealTimeMode
	{
		System::String ^ StlWStringToString( std::wstring const & os )
		{
			String^ str = gcnew String( os.c_str() );
			return str;
		}
		std::wstring *path = nullptr, *tmpPath = nullptr;
		int maxLineLength, maxTimeBetweenEvents;
		DataGridView^  dataGridView1;
		CheckBox ^checkBox2;

		public:


		ThreadRealTimeMode( std::wstring &path, int maxLineLength, DataGridView^  dataGridView, CheckBox ^checkBox, int mTBE )
		{
			this->path = new std::wstring( path );
			this->maxLineLength = maxLineLength;
			dataGridView1 = dataGridView;
			checkBox2 = checkBox;
			maxTimeBetweenEvents = mTBE;
		}

		void ThreadEntryPoint()
		{
			try
			{
				wchar_t tmp[4096];
				GetTempPathW( 4096, tmp);
				tmpPath = new std::wstring( std::wstring(tmp) + L"\CSparcer.logtmp" );

				long long lastPos = 0;
				int errors = 0;
				bool ind;
				std::vector<std::wstring> s;

				size_t maxLineToRead = 50;

				lastPos = ReadFromEnd::GetLastPosition( *path );

				ThreadRealTime ^ReadToEnd = gcnew ThreadRealTime( path, tmpPath, maxLineToRead, maxLineLength );
				Thread ^t3;

				while( true )
				{
					ReadToEnd->curStart = lastPos; //Устанавливаем на начало конца файла
					t3 = gcnew Thread( gcnew ThreadStart( ReadToEnd, &ThreadRealTime::ThreadEntryPoint ) );
					t3->Start(); t3->Join();

					//if( ReadToEnd->error > 0 )
					//return;


					if( lastPos == ReadToEnd->curpos || ReadToEnd->curpos == 0 )
					{
						Sleep( 200 );
						continue;
					}

					lastPos = ReadToEnd->curpos;
					//MessageBox::Show( "fileChanged", "Предупреждение.", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information );


					//Parcing and printing tmpPtath
					size_t reportSize = 0;
					ThreadX^ o1 = gcnew ThreadX( *tmpPath, &reportSize, maxLineLength, maxTimeBetweenEvents, false );
					Thread^ t1 = gcnew Thread( gcnew ThreadStart( o1, &ThreadX::ThreadEntryPoint ) );
					t1->Start(); t1->Join();

					//wchar_t c[10];
					//MessageBox::Show( "in mainCycle of realTime: " + StlWStringToString(_itow( reportSize, c, 10)));
					/*if( dataGridView1->RowCount > 30 ){
						dataGridView1->Rows->Clear();
						dataGridView1->Refresh(); 
						Sleep(200);
					}*/
					//if( dataGridView1->RowCount > 23 )
					//	dataGridView1->FirstDisplayedScrollingRowIndex = 1;

					ind = true;
					for( size_t i = 0; i < reportSize; i++ )
					{
						s = o1->Report->at( i );

						if( StlWStringToString( s[0] ) == L"0/100/0 0:0:0.0" )
						{
							if( ind )
								dataGridView1->RowTemplate->DefaultCellStyle->BackColor = System::Drawing::Color::White, ind = false;
							else
								dataGridView1->RowTemplate->DefaultCellStyle->BackColor = System::Drawing::Color::LightGray, ind = true;
							dataGridView1->Rows->Add( 1 );
						} else
						{
							dataGridView1->Rows->Add( StlWStringToString( s[0] ),
																				StlWStringToString( s[1] ),
																				StlWStringToString( s[2] ),
																				StlWStringToString( s[3] ),
																				StlWStringToString( s[5] ),
																				StlWStringToString( s[4] ),
																				StlWStringToString( s[6] ) );
						}

					}
					s.clear();
					o1->FreePars();
					if(checkBox2->CheckState == CheckState::Checked )
						SendKeys::SendWait( "{PGDN}" );
				}

				//Пытаемся удалить tmpPath
				try { 
					if( IO::File::Exists( StlWStringToString( *tmpPath ) ) )
							IO::File::Delete( StlWStringToString( *tmpPath ) );
				} catch( Exception ^ex )
				{
					MessageBox::Show( "Невозможно удалить временный файл \"" + StlWStringToString( *tmpPath ) + "\"\n" + ex,
														"Предупреждение",
														System::Windows::Forms::MessageBoxButtons::OK,
														System::Windows::Forms::MessageBoxIcon::Information );
				}
				if( path != nullptr ) delete path;
				if( tmpPath != nullptr ) delete tmpPath;

			} catch( Exception^ex )
			{
				if( dynamic_cast< ThreadAbortException ^>( ex ) == nullptr )
					MessageBox::Show( "" + ex,
														"Непредвиденная Ошибка",
														System::Windows::Forms::MessageBoxButtons::OK,
														System::Windows::Forms::MessageBoxIcon::Information ); 
				try
				{
					if( IO::File::Exists( StlWStringToString( *tmpPath ) ) )
						IO::File::Delete( StlWStringToString( *tmpPath ) );
				} catch( Exception ^ex )
				{
					//MessageBox::Show( "Невозможно удалить временный файл \"" + StlWStringToString( *path + L"_.logtmp" ) + "\"\n" + ex,
					//									"Предупреждение",
					//									System::Windows::Forms::MessageBoxButtons::OK,
					//									System::Windows::Forms::MessageBoxIcon::Information );
				}

				if( path != nullptr ) delete path; 
				if( tmpPath != nullptr ) delete tmpPath;
			}

		}

	};

}