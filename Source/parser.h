#ifndef _PARSER_
#define _PARSER_

#include <string>
#include <vector>

#include "service.h"


class Parser
{
public:
	/*!
	@brief constructor that parse file with specific path

	@param[in] path  path to file that will be parsed
	@param[in] strLenght  maximum lenght of lines in file
	 */
	Parser(std::wstring path, size_t strLenght, int maxTimeBetweenElem);
	
	/*!
	@brief parse file with specific path

	Parse file and sorts events to containers,
	if file data is wrong or file doesn't exist, 
	an _error will be set true

	@param[in] path  path to file that will be parsed

	@return true if was an error in data or file
	 */
	size_t parseFile(std::wstring path);

	/*!
	@brief check if in file or data was an error

	@return true if was an error in data or file
	*/
	size_t parseError() const;

	/*!
	@brief return wstring table with all events report

	Table had 7 columns

	@return wstring double array with all events report
	*/
	std::vector<std::vector<std::wstring>> *getEvents(const bool onlyReports = true);

	/*!
	@brief return the number of events of events report

	@return size of events report
	*/
	size_t getEventsSize(const bool onlyReports = true) const;

	void setStrLenght(size_t strLenght);

	int maxTimeBetweenEvents;

private:

	/// event with all needed fields
	struct Event {
		logparsercs::Time eventTime;
		std::wstring cardId;
		std::wstring eventSourceId;
		std::wstring slaveId;
		std::wstring slaveReaderId;
		std::wstring eventDescription;
		std::wstring logFragment;
	};

	///
	size_t lineLenght;

	/// uses for contain an error of parsing file
	size_t _error;

	/// container for all events
	std::vector<Event> _events;

	/// container for all uncorrect events
	std::vector<Event> _eventsReport;
};
#endif