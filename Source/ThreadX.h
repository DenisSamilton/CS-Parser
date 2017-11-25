#include "stdafx.h"
#include "vector"
#include "string.h"
#include "parser.h"

namespace logparsercs
{
    public ref class ThreadX
    {
       std::wstring *pathF = nullptr;
       volatile size_t *_size;
       size_t _maxStrlength;
			 int maxTimeBetweenEvents;
			 bool _onlyReports;
       Parser *_pars = nullptr;
	
        public:
				void FreePars(){ 
						if( _pars != nullptr ) delete _pars;
						if( Report != nullptr ) delete Report;
				};

        std::vector<std::vector<std::wstring>> *Report = nullptr;
        int errorlevel = 0;

        ThreadX( std::wstring path, volatile size_t *sizes, int maxStrlength, int mTBI, bool onlyReports )
        {
            pathF = new std::wstring(path);
            _size = sizes; 
						_maxStrlength = maxStrlength;
						_onlyReports = onlyReports;
						maxTimeBetweenEvents = mTBI;
        }

        void ThreadEntryPoint()
        {
            _pars = new Parser( *pathF, _maxStrlength, maxTimeBetweenEvents );
            Report = _pars->getEvents( _onlyReports );
            *_size = _pars->getEventsSize( _onlyReports );
						errorlevel += _pars->parseError();
						if( pathF != nullptr ) delete pathF;
        }
    };

}