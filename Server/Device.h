#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include "DeviceParameter.h"

class Device
{
private:
	std::string name;
	std::vector<DeviceParameter*> parameters;
	bool status; // true = ON, false = OFF
public:
	Device(std::string name, std::vector<DeviceParameter*> parameters);
	bool isParameterExist(std::string paramName);
	bool addParameter(DeviceParameter* param);
	bool setParameter(std::string parameterName, std::string parameterValue);
	bool getStatus();
	bool setStatus(bool status);
};

#endif // !DEVICE_H
