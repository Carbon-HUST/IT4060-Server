#include "Device.h"

Device::Device(int id, std::string name, std::vector<DeviceParameter*> parameters): id(id), name(name), parameters(parameters)
{
	status = false;
}

bool Device::isParameterExist(std::string paramName)
{
	for (DeviceParameter* parameter : parameters)
	{
		if (parameter->getName() == paramName)
			return true;
	}
	return false;
}

bool Device::addParameter(DeviceParameter * param)
{
	if (isParameterExist(param->getName()))
		return false;
	parameters.push_back(param);
	return true;
}

bool Device::setParameter(std::string parameterName, std::string parameterValue)
{
	DeviceParameter* paramFound = NULL;
	for (DeviceParameter* param : parameters)
	{
		if (parameterName == param->getName())
		{
			paramFound = param;
			break;
		}
	}
	if (paramFound == NULL)
		return false;
	if (paramFound->setValue(parameterValue))
		return false;
	return true;
}

bool Device::getStatus()
{
	return status;
}

bool Device::setStatus(bool status)
{
	if (this->status == status)
		return false;
	return true;
}

int Device::getId()
{
	return id;
}

std::string Device::getName()
{
	return name;
}
;
