#include "Aerator.h"

Aerator::Aerator(int id, std::string name, std::vector<DeviceParameter*> parameters) : Device(id, name, parameters)
{
	// aerator has 2 parameter: C (fan speed) and a vector of timerange
	SingleDeviceParameter<double> *fanSpeed = new SingleDeviceParameter<double>("C", "Fan Speed", 1000);

	std::vector<TimeRange> trs;
	MultipleDeviceParameter<TimeRange> *timeRanges = new MultipleDeviceParameter<TimeRange>("TR", "Time ranges", trs);

	this->addParameter(fanSpeed);
	this->addParameter(timeRanges);
}
