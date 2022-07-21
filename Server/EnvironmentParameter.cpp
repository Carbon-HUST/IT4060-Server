#include "EnvironmentParameter.h"

EnvironmentParameter::EnvironmentParameter(std::string name, std::string unitOfMeasurement)
	: name(name), unitOfMeasurement(unitOfMeasurement)
{
}

std::string EnvironmentParameter::getName()
{
	return name;
}

std::string EnvironmentParameter::getUnitOfMeasurement()
{
	return unitOfMeasurement;
}

double EnvironmentParameter::getValue()
{
	double random = (double)std::rand() / RAND_MAX;
	return random * (max - min) + min;
}

double getEnvironmentParameterValue(std::vector<EnvironmentParameter>& evParam, std::string name, bool & isFound)
{
	for (auto& param : evParam)
	{
		if (param.getName() == name)
		{
			isFound = true;
			return param.getValue();
		}
	}
	isFound = false;
	return 0.0;
}
