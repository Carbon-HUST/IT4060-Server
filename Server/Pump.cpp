#include "Pump.h"


Pump::Pump(int id, std::string name, std::vector<DeviceParameter*> parameters) : Device(id, name, parameters)
{

	// initial status = false (Pump is turned off)

	// parameter of pump : V (flow rate) and operating time T	
	SingleDeviceParameter<double> *flowRate = new SingleDeviceParameter<double>("V", "Flow Rate", 9);
	SingleDeviceParameter<int> *operatingTime = new SingleDeviceParameter<int>("T", "Operating Time", 1);

	//add parameters when creating an instance of Pump
	this->addParameter(flowRate);
	this->addParameter(operatingTime);
}





