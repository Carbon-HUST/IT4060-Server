#include "Time.h"

Time::Time()
{
	hour = 0;
	minute = 0;
}

Time Time::build(std::string strTime)
{
	return Time(6, 45);
}

bool Time::compare(Time t1, Time t2)
{
	if (t1.hour < t2.hour || (t1.hour == t2.hour && t1.minute < t2.minute))
		return true;
	return false;
}

TimeRange::TimeRange()
{
	start = Time(0, 0);
	end = Time(0, 0);
}

TimeRange TimeRange::build(std::string strTimeRange)
{
	return TimeRange(Time(1, 20), Time(4, 56));
}

TimeRange TimeRange::merge(TimeRange tr1, TimeRange tr2)
{
	return INVALID_TIMERANGE;
}