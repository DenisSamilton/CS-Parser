#include "stdafx.h"
#include "parser.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>
#include <cstdlib>

#include "service.h"

using namespace std;


Parser::Parser(std::wstring path, size_t strLenght, int maxTimeBetweenElem)
{
	lineLenght = strLenght;
	this->maxTimeBetweenEvents = maxTimeBetweenElem;
	parseFile(path);
}

size_t Parser::parseFile(std::wstring path)
{
	_error = false;
  _eventsReport.clear();

	wifstream logFile(path);
	if (!logFile.is_open()) {
		_error = true;
		return true;
	}
	
	try {
		while (!logFile.eof()) {
			Event event;
			wstringstream stream(L"");

			wstring tmp( L"" ), tmpSecond(L"");
			wchar_t *tmpChar = nullptr;

			// Log fragment
			tmpChar = new wchar_t[lineLenght];

			logFile.getline(tmpChar, lineLenght ); //System::Windows::Forms::MessageBox::Show( gcnew System::String( tmpChar ), "Warning.", System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Information );

			event.logFragment = tmpChar; //System::Windows::Forms::MessageBox::Show( "After\"event.logFragment = tmpChar;\"\n"+gcnew System::String( event.logFragment.c_str() ) );
			stream << tmpChar;

			if( tmpChar != nullptr )
				delete[] tmpChar;
			//wifstream debug(L"")
			bool isExit = false;

			size_t cONDS; //countOfNotDigitSymbols
			for( cONDS=1; (cONDS < 7) && (!iswdigit( stream.get() )); cONDS++ )
			{
				if( stream.eof() )
				{
					isExit = true;
					break;
				}
				stream.ignore( 1 );
			}

			if( cONDS >= 7 || isExit )
				continue;

			stream.unget(); 

			// Time
			stream >> tmp;

			event.eventTime.month = stoi(wstring() + tmp[0] + tmp[1]);
			event.eventTime.day = stoi(wstring() + tmp[3] + tmp[4]);
			event.eventTime.year = stoi(wstring() + tmp[6] + tmp[7]);

			tmpChar = new wchar_t[4];

			stream.ignore();

			stream.get(tmpChar, 3, ':');
			stream.ignore();
			event.eventTime.hours = stoi(tmpChar);

			stream.get(tmpChar, 3, ':');
			stream.ignore();
			event.eventTime.min = stoi(tmpChar);

			stream.get(tmpChar, 3, '.');
			stream.ignore();
			event.eventTime.sec = stoi(tmpChar);

			stream.get(tmpChar, 4, ' ');
			stream.ignore();
			event.eventTime.millisec = stoi(tmpChar);

			delete[] tmpChar;

			// Ingnoring unnesessary hex data
			stream.ignore(21);

			// Checking on events
			stream >> tmp;

			while (tmp == L"83" || tmp == L"82") {
				bool throwToReports = false; 
				bool checkByWarning = false;
				
				//System::Windows::Forms::MessageBox::Show( "After\"while(tmp == L\"83\"...\"\n" + gcnew System::String( event.logFragment.c_str() ) );
				if (tmp == L"83") {
					// Event size in bytes
					size_t dataSize;
					stream >> tmp;
					logparsercs::hexToDec(tmp, dataSize);

					// Ingnoring date/time
					stream.ignore(12);
					dataSize -= 4;

					// Event source id
					stream >> tmp >> tmpSecond;
					if (tmpSecond == L"00") {
						event.eventSourceId = L"00 " + tmp;
					}
					else {
						event.eventSourceId = tmp + L' ' + tmpSecond;
					}
					dataSize -= 2;

					// Event code DM-01
					stream >> tmp;
					size_t realEventCode;
					logparsercs::hexDmToDec(tmp, realEventCode);

					if (realEventCode == 1) {
						event.eventDescription = L"381";

						// Ingnoring unnesessary hex data
						stream.ignore(10);

						// Card ID
						tmpChar = new wchar_t[15];

						stream.get(tmpChar, 15);
						event.cardId = tmpChar;

						delete[] tmpChar;

						dataSize -= 9;
					}
					else if (realEventCode == 5) {
						event.eventDescription = L"385";
						dataSize -= 1;
					}
					else if (realEventCode == 6) {
						event.eventDescription = L"386";
						dataSize -= 1;
					}
					else if (realEventCode == 7) {
						event.eventDescription = L"387";
						dataSize -= 1;
					}
					else if (realEventCode == 8) {
						event.eventDescription = L"388";
						dataSize -= 1;
					}
					else if (realEventCode == 9) {
						event.eventDescription = L"389";
						dataSize -= 1;
					}
					else if (realEventCode == 10) {
						event.eventDescription = L"310";
						dataSize -= 1;
					}
					else if (realEventCode == 11) {
						event.eventDescription = L"311";
						dataSize -= 1;
					}
					else if (realEventCode == 12) {
						event.eventDescription = L"312";
						dataSize -= 1;
					}
					else if (realEventCode == 13) {
						event.eventDescription = L"313";
						dataSize -= 1;
					}
					else if (realEventCode == 14) {
						event.eventDescription = L"314";
						dataSize -= 1;
					}
					else if (realEventCode == 15) {
						event.eventDescription = L"315";
						dataSize -= 1;
					}
					else if (realEventCode == 16) {
						event.eventDescription = L"316";
						dataSize -= 1;
					}
					else if (realEventCode == 17) {
						event.eventDescription = L"317";
						dataSize -= 1;
					}
					else if (realEventCode == 18) {
						event.eventDescription = L"318";
						dataSize -= 1;
					}
					else if (realEventCode == 19) {
						event.eventDescription = L"319";

						// Ingnoring unnesessary hex data
						stream.ignore(6);

						dataSize -= 3;
					}
					else if (realEventCode == 20) {
						event.eventDescription = L"320";
						dataSize -= 1;
					}
					else if (realEventCode == 21) {
						event.eventDescription = L"321";
						dataSize -= 1;
					}
					else if (realEventCode == 22) {
						event.eventDescription = L"322";
						dataSize -= 1;
					}
					else if (realEventCode == 23) {
						event.eventDescription = L"323";
						dataSize -= 1;
					}
					else if (realEventCode == 24) {
						event.eventDescription = L"324";
						dataSize -= 1;
					}
					else if (realEventCode == 25) {
						event.eventDescription = L"325";
						dataSize -= 1;
					}
					else if (realEventCode == 26) {
						event.eventDescription = L"326";

						// Ingnoring unnesessary hex data
						stream.ignore(10);

						// Card ID
						tmpChar = new wchar_t[15];

						stream.get(tmpChar, 15);
						event.cardId = tmpChar;

						delete[] tmpChar;
						dataSize -= 9;
					}
					else {
							_eventsReport.push_back( event );
							_eventsReport.push_back( { 100 } );
							_events.push_back( event );
							_error++;
							stream.clear();
							continue;
						//throw exception((string("error while reading event code DM-01: ") + to_string( _wtoi(tmp.c_str()))).c_str());
					}

					// Ingnoring unnesessary hex data
					if (dataSize > 0)
						stream.ignore(dataSize * 3);

					event.slaveId = ' ';
					event.slaveReaderId = ' ';
          _events.push_back(event);

				}else if (tmp == L"82") {
					// Event size in bytes
					size_t dataSize;
					stream >> tmp;
					logparsercs::hexToDec(tmp, dataSize);

					// Ingnoring date/time
					stream.ignore(12);
					dataSize -= 4;

					// Event source id
					stream >> tmp >> tmpSecond;
					if (tmpSecond == L"00") {
						event.eventSourceId = L"00 " + tmp;
					}
					else {
						event.eventSourceId = tmp + L' ' + tmpSecond;
					}
					dataSize -= 2;

					// Event code KV-02
					stream >> tmp;
					if (dataSize == 14) {
						switch (tmp[1]) {
						case '1':
							event.eventDescription = L"21";
							break;
						case '2':
							event.eventDescription = L"22";
							break;
						case '3':
							event.eventDescription = L"23";
							break;
						case '4':
							event.eventDescription = L"24";
							break;
						case '5':
							event.eventDescription = L"25";
							break;
						case '6':
							event.eventDescription = L"26";
							break;
						case '7':
							event.eventDescription = L"27";
							break;
						case '8':
							event.eventDescription = L"28";

							checkByWarning = true;
							break;
						case '9':
							event.eventDescription = L"29";
							break;
						case 'A':
							event.eventDescription = L"2A";
							break;
						case 'B':
							event.eventDescription = L"2B";

							checkByWarning = true;
							break;
						case 'C':
							event.eventDescription = L"2C";
							break;
						case 'D':
							event.eventDescription = L"2D";
							break;
						case 'E':
							event.eventDescription = L"2E";
							break;
						default:
              event.eventDescription = L"NULL";
							_error++;
							//throw exception("error while reading event code KV-02");
						}

						// Ingnoring unnesessary hex data
						stream.ignore(3);
						dataSize -= 1;

						// Slave id
						stream >> tmp >> tmpSecond;
						if (tmpSecond == L"00") {
							event.slaveId = L"00 " + tmp;
						}
						else {
							event.slaveId = tmp + L' ' + tmpSecond;
						}
						dataSize -= 2;

						// Slave reader id
						stream >> tmp;
						event.slaveReaderId = tmp;
						dataSize -= 1;

						// Card ID
						tmpChar = new wchar_t[15];

						stream.ignore(1);
						stream.get(tmpChar, 15);
						event.cardId = tmpChar;

						delete[] tmpChar;

						dataSize -= 5;
					}
					else {
						switch (tmp[1]) {
						case '1':
							event.eventDescription = L"11";
							throwToReports = true;
							break;
						case '2':
							event.eventDescription = L"12";
							break;
						case '3':
							event.eventDescription = L"13";
							throwToReports = true;

							// Slave id
							stream >> tmp >> tmpSecond;
							if (tmpSecond == L"00") {
								event.slaveId = L"00 " + tmp;
							}
							else {
								event.slaveId = tmp + L' ' + tmpSecond;
							}
							dataSize -= 2;

							break;
						case '4':
							event.eventDescription = L"14";
							throwToReports = true;

							// Slave id
							stream >> tmp >> tmpSecond;
							if (tmpSecond == L"00") {
								event.slaveId = L"00 " + tmp;
							}
							else {
								event.slaveId = tmp + L' ' + tmpSecond;
							}
							dataSize -= 2;

							break;
						case '5':
							event.eventDescription = L"15";

							// Card ID
							tmpChar = new wchar_t[15];

							stream.get(tmpChar, 15);
							event.cardId = tmpChar;

							delete[] tmpChar;

							dataSize -= 5;

							break;

						default:
							event.eventDescription = L"NULL";
							_error++;
							//throw exception("error while reading event code KV-02");
						}
					}
					dataSize -= 1;

					// Ingnoring unnesessary hex data
					if (dataSize > 0)
						stream.ignore(dataSize * 3);

					_events.push_back(event);

					/*if (checkByWarning) {
						for (auto &i : _events)
							if (i.cardId == event.cardId)
								_eventsReport.push_back(i);

						throwToReports = true;
					}*/
					if( checkByWarning )
					{
						for( auto i = _events.rbegin(); i < _events.rend(); ++i )
							if( i->cardId == event.cardId && logparsercs::calcTimeDiff( event.eventTime, i->eventTime ) <= maxTimeBetweenEvents )
								_eventsReport.push_back( *i );

						throwToReports = true;
					}

					if (throwToReports) {
						_eventsReport.push_back(event);
						_eventsReport.push_back({ 100 });
					}
				}

				stream >> tmp;
			}

			stream.clear();
		}
	}
	catch (exception exc) {
        //System::Windows::Forms::MessageBox::Show( gcnew System::String( exc.what()), "Непредвиденная Ошибка");
		cout << "Error: " << exc.what() << endl;
	}
	catch (...) {
        //System::Windows::Forms::MessageBox::Show( "Непредвиденная Ошибка" );
		_error++;
	}

	//_events.clear();
	logFile.close();
	return _error;
}

size_t Parser::parseError() const
{
	return _error;
}

std::vector<std::vector<std::wstring>> *Parser::getEvents(const bool onlyReports)
{   
	auto outputTable = new std::vector<std::vector<std::wstring>>;

	std::vector<Event> *events = nullptr;
	size_t eventsSize = 0;

	//wchar_t c[10];
	//System::Windows::Forms::MessageBox::Show( "к-во у Дена:"+gcnew System::String( _itow( _events.size(), c, 10 ) ) );

	if (onlyReports) {
		events  = &_eventsReport;
		eventsSize = _eventsReport.size();
		_events.clear();
	} else {
		events = &_events;
		eventsSize = _events.size();
		_eventsReport.clear();
	}

	for (size_t i = 0; i < eventsSize; i++) {
		wstring tmp;
		vector<wstring> tmpVec;

		tmp = to_wstring((*events)[i].eventTime.month) + L'/' + to_wstring((*events)[i].eventTime.day) + L'/' 
		+ to_wstring((*events)[i].eventTime.year)
		+ L' ' + to_wstring((*events)[i].eventTime.hours) + L':' + to_wstring((*events)[i].eventTime.min) + L':' 
		+ to_wstring((*events)[i].eventTime.sec) + L'.' + to_wstring((*events)[i].eventTime.millisec);
		tmpVec.push_back(tmp);

		tmpVec.push_back((*events)[i].cardId);
		tmpVec.push_back((*events)[i].eventSourceId);
		tmpVec.push_back((*events)[i].slaveId);
		tmpVec.push_back((*events)[i].slaveReaderId);

		// Event 83
		if ((*events)[i].eventDescription == L"381")
			tmp = L"Поднесение карточки к считывателю";
		else if ((*events)[i].eventDescription == L"385")
			tmp = L"Нажатие кнопки открытия двери";
		else if ((*events)[i].eventDescription == L"386")
			tmp = L"Срабатывание датчика открытия двери (открытие)";
		else if ((*events)[i].eventDescription == L"387")
			tmp = L"Срабатывание датчика открытия двери (закрытие)";
		else if ((*events)[i].eventDescription == L"388")
			tmp = L"Срабатывание защелки (открытие по команде интерфейса)";
		else if ((*events)[i].eventDescription == L"389")
			tmp = L"Переход в режим разрешения прохода по нажатию кнопки";
		else if ((*events)[i].eventDescription == L"310")
			tmp = L"Срабатывание защелки (закрытие)";
		else if ((*events)[i].eventDescription == L"311")
			tmp = L"Срабатывание тампера (вскрытие корпуса)";
		else if ((*events)[i].eventDescription == L"312")
			tmp = L"Срабатывание тампера (закрытие корпуса)";
		else if ((*events)[i].eventDescription == L"313")
			tmp = L"Переход в режим свободного прохода";
		else if ((*events)[i].eventDescription == L"314")
			tmp = L"Переход в режим блокировки прохода";
		else if ((*events)[i].eventDescription == L"315")
			tmp = L"Переход в режим разрешения прохода по команде мастера";
		else if ((*events)[i].eventDescription == L"316")
			tmp = L"Переход в режим запрещения прохода по команде мастера";
		else if ((*events)[i].eventDescription == L"317")
			tmp = L"Переход в дежурный по таймауту ожидания";
		else if ((*events)[i].eventDescription == L"318")
			tmp = L"Обнаружение аварии линии связи";
		else if ((*events)[i].eventDescription == L"319")
			tmp = L"Переход в режим ожидания закрытия двери";
		else if ((*events)[i].eventDescription == L"320")
			tmp = L"Переход в режим незакрытой двери;";
		else if ((*events)[i].eventDescription == L"321")
			tmp = L"Переход в дежурный режим по закрытию двери";
		else if ((*events)[i].eventDescription == L"322")
			tmp = L"Срабатывание датчика открытия двери, когда проход не разрешен(несанкционированное открытие)";
		else if ((*events)[i].eventDescription == L"323")
			tmp = L"Переход в режим генерации сообщения пользователю";
		else if ((*events)[i].eventDescription == L"324")
			tmp = L"Возврат из режима генерации сообщения пользователю";
		else if ((*events)[i].eventDescription == L"325")
			tmp = L"Восстановление связи";
		else if ((*events)[i].eventDescription == L"326")
			tmp = L"Проход по карточке. Спец событие";

		// Event 82, dataSize == 14
		else if ((*events)[i].eventDescription == L"21")
			tmp = L"Доступ разрешен";
		else if ((*events)[i].eventDescription == L"22")
			tmp = L"Неизвестная ошибка";
		else if ((*events)[i].eventDescription == L"23")
			tmp = L"Доступ запрещен, отсутствует пропуск";
		else if ((*events)[i].eventDescription == L"24")
			tmp = L"Доступ запрещен, отсутствует группа";
		else if ((*events)[i].eventDescription == L"25")
			tmp = L"Доступ запрещен по точке прохода";
		else if ((*events)[i].eventDescription == L"26")
			tmp = L"Доступ запрещен, отсутствует цикл";
		else if ((*events)[i].eventDescription == L"27")
			tmp = L"Доступ запрещен по времени доступа";
		else if ((*events)[i].eventDescription == L"28")
			tmp = L"Доступ запрещен нарушение правил прохода зон";
		else if ((*events)[i].eventDescription == L"29")
			tmp = L"Доступ запрещен праздничный день";
		else if ((*events)[i].eventDescription == L"2A")
			tmp = L"Доступ запрещен выходной день";
		else if ((*events)[i].eventDescription == L"2B")
			tmp = L"Доступ разрешен с предупреждением правил прохода зон";
		else if ((*events)[i].eventDescription == L"2C")
			tmp = L"Доступ запрещен по сроку действия пропуска";
		else if ((*events)[i].eventDescription == L"2D")
			tmp = L"Доступ запрещен пропуск заблокирован";
		else if ((*events)[i].eventDescription == L"2E")
			tmp = L"Автоматическая блокировка пропуска";

		// Event 82, dataSize != 14
		else if ((*events)[i].eventDescription == L"11")
			tmp = L"Включение устройства";
		else if ((*events)[i].eventDescription == L"12")
			tmp = L"Ошибка тестирования";
		else if ((*events)[i].eventDescription == L"13")
			tmp = L"Подключение подчиненного устройства";
		else if ((*events)[i].eventDescription == L"14")
			tmp = L"Отключение подчиненного устройства";
    else if ((*events)[i].eventDescription == L"15" )
            tmp = L"Запрашиваемый регламент отсутствует";
    else tmp = L"NULL";

		tmpVec.push_back(tmp);

		tmpVec.push_back((*events)[i].logFragment);

		outputTable->push_back(tmpVec);
	}

	return outputTable;
}

size_t Parser::getEventsSize(const bool onlyReports) const
{
	if (onlyReports)
		return _eventsReport.size();
	else
		return _events.size();
}

void Parser::setStrLenght( size_t strLenght )
{
    lineLenght = strLenght;
}