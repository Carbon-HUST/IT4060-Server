#include "QuicklimeDispenser.h"

QuicklimeDispenser::QuicklimeDispenser(int id, std::string name, std::vector<DeviceParameter> parameters)
{
	SingleDeviceParameter<double> *limeAmount = new SingleDeviceParameter<double>("L", "Lime Amount", 100);
	this->addParameter(limeAmount);
}
