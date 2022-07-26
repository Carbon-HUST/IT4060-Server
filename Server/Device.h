#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include "DeviceParameter.h"

class Device
{
private:
	int id;
	std::string name;
	std::vector<DeviceParameter*> parameters;
	bool status; // true = ON, false = OFF
public:
	Device(int id, std::string name, std::vector<DeviceParameter*> parameters);
	bool isParameterExist(std::string paramName);
	bool addParameter(DeviceParameter* param);
	bool setParameter(std::string parameterName, std::string parameterValue);
	bool getStatus();
	bool setStatus(bool status);
	int getId();
	std::string getName();
	std::string getParameter(std::string name);
	virtual std::string getDeviceType();
};

#endif // !DEVICE_H
