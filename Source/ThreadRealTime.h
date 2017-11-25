#include "stdafx.h"
#include "readfromend.h"

namespace logparsercs
{
    public ref class ThreadRealTime
    {
        std::wstring *path = nullptr, *tmpPath = nullptr;
        size_t maxLineToRead;
        int maxLineLength;
        ReadFromEnd *rfe = nullptr;


        public:
				long long curStart;
        int error = 0;
        long curpos = 0;

        ThreadRealTime( std::wstring *path, std::wstring *tmpPath, size_t maxLineToRead, int maxLineLength )
        {
            //curstart = curPos;
            this->path = new std::wstring( *path );
            this->tmpPath = new std::wstring( *tmpPath );
            this->maxLineToRead = maxLineToRead;
            this->maxLineLength = maxLineLength;
        }

        void ThreadEntryPoint()
        {
            rfe = new ReadFromEnd( *path, *tmpPath, curStart, maxLineToRead, maxLineLength );
            error = rfe->error;
            curpos = rfe->curpos;
						if( rfe != nullptr ) delete rfe;
						/*if( path != nullptr ) delete path; // Не нужно удалять, потому что используется в риал тайме постоянно
						if( tmpPath != nullptr ) delete tmpPath;*/
        }
    };

}