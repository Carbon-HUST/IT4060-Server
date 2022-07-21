#ifndef ENVIRONMENT_PARAMETER_H
#define ENVIRONMENT_PARAMETER_H

#include <string>
#include <vector>
#include <cstdlib>

class EnvironmentParameter
{
private:
	std::string name;
	std::string unitOfMeasurement;
	double min;
	double max;

public:
	EnvironmentParameter(std::string name, std::string unitOfMeasurement);
	std::string getName();
	std::string getUnitOfMeasurement();
	double getValue();
};

double getEnvironmentParameterValue(std::vector<EnvironmentParameter>& evParam, std::string name, bool& isFound);

#endif // !ENVIRONMENT_PARAMETER_H
