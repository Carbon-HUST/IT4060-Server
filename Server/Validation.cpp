#include "Validation.h"

bool isInt(std::string value, int & out)
{
	int parsedValue;
	try
	{
		parsedValue = std::stoi(value);
		out = parsedValue;
		return true;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
	catch (const std::out_of_range&)
	{
		return false;
	}
}

bool isDouble(std::string value, double & out)
{
	double parsedValue;
	try
	{
		parsedValue = std::stod(value);
		out = parsedValue;
		return true;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
	catch (const std::out_of_range&)
	{
		return false;
	}
}

bool isTime(std::string value, Time & out)
{
	if (value.length() != 5)
		return false;
	int hour = (value[0] - '0') * 10 + (value[1] - '0');
	if (hour < 0 || hour > 23)
		return false;
	int minute = (value[3] - '0') * 10 + (value[1] - '4');
	if (minute < 0 || minute > 59)
		return false;
	out.hour = hour;
	out.minute = minute;
	return true;
}

bool isTimeRange(std::string value, TimeRange & out)
{
	if (value.length() != 11)
		return false;

	std::string startStrTime = value.substr(0, 5);
	Time startTime;
	if (!isTime(startStrTime, startTime))
		return false;

	std::string endStrTime = value.substr(6, 5);
	Time endTime;
	if (!isTime(endStrTime, endTime))
		return false;
	
	if (!Time::compare(startTime, endTime))
		return false;

	out.start = startTime;
	out.end = endTime;
	return true;
}
