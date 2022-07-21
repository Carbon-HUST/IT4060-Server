#include "DeviceParameter.h"

DeviceParameter::DeviceParameter(std::string name, DeviceParameterType parameterType): name(name), parameterType(parameterType)
{

};

std::string DeviceParameter::getName()
{
	return name;
}

DeviceParameterType DeviceParameter::getParameterType()
{
	return parameterType;
}

