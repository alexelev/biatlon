#include "protos.h"



Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::invalid_format(uint line_number)
{
	string message = "Line #" + to_string(line_number) + ": Invalid data format.";
	messages.push(message);
}

void Logger::invalid_stage_number(string line_number) {
	string message = "Line #" + line_number + ": Invalid stage number. The stage number is greater than the one indicated in the header.";
	messages.push(message);
}

void Logger::invalid_total_misses() {
	string message = "The number of misses does not match the calculated value.";
	messages.push(message);
}

void Logger::invalid_start_validation()
{
	string message = "Something went wrong: wrong header format or wrong footer format or wrong number of records.";
	messages.push(message);
}

void Logger::invalid_phisycal_state()
{
	string message = "The file is not open";
	messages.push(message);
}

void Logger::show()
{
	if (messages.get_size() > 0) {
		messages.show();
	}
}

DStore<string> Logger::messages;