#include "stdafx.h"
#include "windows.h"
#include <cstdio>

const size_t MIN_FILE_LENGTH = 98058462 * 2; //98058462 * 2 Байт - это 4 дня в логе

class Devide{
    long filesize( FILE *stream )
    {
        long curpos, length;
        /* сохранить текущее положение указателя */
        curpos = ftell( stream );
        /* перейти в конец файла */
        fseek( stream, 0L, SEEK_END );
        /* получить текущее положение указателя */
        length = ftell( stream );
        /* восстановить старое положение */
        fseek( stream, curpos, SEEK_SET );
        return(length);
    }

    public:
    bool error = 0;
    std::wstring *DevideFiles( std::wstring path, int &count, int maxStrSize )
    {
        std::wstring *pathOfFiles = new std::wstring[count];

        if( count <= 1 )
        {
            pathOfFiles[0] = path;
        } else
        {
            try{
                FILE *pFile;
                _wfopen_s( &pFile, path.c_str(), L"r, ccs=UTF-8" );
                if( !pFile ){
                    System::Windows::Forms::MessageBox::Show( "File" + gcnew System::String(path.c_str()) + "opening failed", "Error" );
                    error = 1; return nullptr;
                }

                FILE *pFileTmp;

                long sizeF = filesize( pFile );
                    if( sizeF < MIN_FILE_LENGTH )
                    { 
                        count = 1;
                        pathOfFiles[0] = path;
                        return pathOfFiles;
                    }

                long partSize = sizeF / count;
                long start_pos = ftell( pFile );
                wchar_t *buf = new wchar_t[maxStrSize];
                for( int i=0; i <= count-2; i++ )
                {
                    pathOfFiles[i] = path + L"_" + std::to_wstring( i ) + L".logtmp";

                    _wfopen_s( &pFileTmp, pathOfFiles[i].c_str(), L"w, ccs=UTF-8" );

                    if( !pFileTmp ){
                        System::Windows::Forms::MessageBox::Show( "File" + gcnew System::String( pathOfFiles[i].c_str() ) + "opening failed", "Error" );
                        error = 1; return nullptr;
                    }
                       
                    while( fgetws( buf, maxStrSize, pFile ) != L'\0' && ftell( pFile ) < (start_pos + partSize) )
                        fputws( buf, pFileTmp );
                    
                    
                   start_pos = ftell( pFile );
                   fclose( pFileTmp );
                }
                pathOfFiles[count-1] = path + L"_" + std::to_wstring( count-1 ) + L".logtmp";
                _wfopen_s( &pFileTmp, pathOfFiles[count-1].c_str(), L"w, ccs=UTF-8" );

                if( !pFileTmp )
                {
                    System::Windows::Forms::MessageBox::Show( "File" + gcnew System::String( pathOfFiles[count-1].c_str() ) + "opening failed", "Error" );
                    error = 1; return nullptr;
                }
                
                while( fgetws( buf, maxStrSize, pFile ) != L'\0' && ftell( pFile ) <sizeF )
                    fputws( buf, pFileTmp );

                fclose( pFileTmp );
                fclose( pFile );
            }catch( ... ){}
        }

        return pathOfFiles;
    }

};