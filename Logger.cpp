#include "protos.h"



Logger::Logger()
{
}


Logger::~Logger()
{
}

void Logger::invalid_format(string line_number)
{
	string message = "Line #" + line_number + ": Invalid data format.";
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

DStore<string> Logger::messages;