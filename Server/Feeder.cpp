#include "Feeder.h"

Feeder::Feeder(int id, std::string name, std::vector<DeviceParameter> parameters) : Device(id, name, parameters)
{
	SingleDeviceParameter<double> *amount = new SingleDeviceParameter<double>("W", "Feeding Amount", 100);
	
	std::vector<Time> tps;
	MultipleDeviceParameter<Time> *times = new MultipleDeviceParameter<Time>("Tp", "Times", tps);

	this->addParameter(amount);
	this->addParameter(times);
}
