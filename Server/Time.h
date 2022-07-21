#ifndef TIME_H
#define TIME_H

#include <string>

struct Time
{
	int hour;
	int minute;

	Time(int hour, int minute) : hour(hour), minute(minute) {};
	Time();

	static Time build(std::string);
	static bool compare(Time, Time);
};

const Time INVALID_TIME = Time(-1, -1);


struct TimeRange
{
	Time start;
	Time end;

	TimeRange(Time start, Time end) : start(start), end(end) {};
	TimeRange();
	static TimeRange build(std::string);
	static TimeRange merge(TimeRange, TimeRange);
};

const TimeRange INVALID_TIMERANGE = TimeRange(INVALID_TIME, INVALID_TIME);

#endif // !TIME_H
