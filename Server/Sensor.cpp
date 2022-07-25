#include "Sensor.h"


double Sensor::getEnvironmentParameterValue(std::vector<EnvironmentParameter>& evParam, std::string name, bool & isFound)
{
	for (auto &param : evParam)
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

