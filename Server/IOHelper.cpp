#include <fstream>
#include <iostream>
#include "IOHelper.h"
#include "Aerator.h"
#include "Pump.h"
#include "Feeder.h"
#include "QuicklimeDispenser.h"
#include "Sensor.h"
#include "EnvironmentParameter.h"

std::string removeString(std::string s)
{
	while (s[0] != ' ')
	{
		s.erase(s.begin());
	}
	s.erase(s.begin());
	return s;
}

bool readDevice(std::string fileName, Device * device, std::string password)
{
	std::string line, nameOfDevice, typeOfDevice;
	std::ifstream readFile(fileName);
	int id;

	if (readFile.is_open())
	{
		std::getline(readFile, line);
		id = stoi(line.substr(0, line.find(' ', 0)));
		removeString(line);
		password = line.substr(0, line.find(' ', 0));
		removeString(line);
		nameOfDevice = line.substr(0, line.find_last_of(' '));
		typeOfDevice = line.substr(line.find_last_of(' ') + 1);
		if (typeOfDevice == "Aerator")
		{
			std::vector<DeviceParameter*> parameters;
			getline(readFile, line);
			int numOfParam = stoi(line);
			while (getline(readFile, line))
			{
				std::string name = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string typeOfParam = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string fullName = line;
				if (name.size() == 1)
				{
					SingleDeviceParameter<double> *param = new SingleDeviceParameter<double>(name, fullName, 0);
					parameters.push_back(param);
				}
				else if (name.size() == 2)
				{
					std::vector<TimeRange> trs;
					MultipleDeviceParameter<TimeRange> *param = new MultipleDeviceParameter<TimeRange>(name, fullName, trs);
					parameters.push_back(param);
				}
			}
			device = new Aerator(id, nameOfDevice, parameters);
		}
		else if (typeOfDevice == "Pump")
		{
			std::vector<DeviceParameter*> parameters;
			getline(readFile, line);
			int numOfParam = stoi(line);
			while (getline(readFile, line))
			{
				std::string name = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string typeOfParam = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string fullName = line;
				if (typeOfParam == "double")
				{
					SingleDeviceParameter<double> *param = new SingleDeviceParameter<double>(name, fullName, 0);
					parameters.push_back(param);
				}
				else if (typeOfParam == "int")
				{

					SingleDeviceParameter<int> *param = new SingleDeviceParameter<int>(name, fullName, 0);
					parameters.push_back(param);
				}
			}
			device = new Pump(id, nameOfDevice, parameters);
		}
		else if (typeOfDevice == "Feeder")
		{
			std::vector<DeviceParameter*> parameters;
			getline(readFile, line);
			int numOfParam = stoi(line);
			while (getline(readFile, line))
			{
				std::string name = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string typeOfParam = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string fullName = line;
				if (name.size() == 1)
				{
					SingleDeviceParameter<double> *param = new SingleDeviceParameter<double>(name, fullName, 0);
					parameters.push_back(param);
				}
				else if (name.size() == 2)
				{
					std::vector<Time> tps;
					MultipleDeviceParameter<Time> *param = new MultipleDeviceParameter<Time>(name, fullName, tps);
					parameters.push_back(param);
				}
			}
			device = new Feeder(id, nameOfDevice, parameters);

		}
		else if (typeOfDevice == "QuicklimeDispenser")
		{
			std::vector<DeviceParameter*> parameters;
			getline(readFile, line);
			int numOfParam = stoi(line);
			while (getline(readFile, line))
			{
				std::string name = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string typeOfParam = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string fullName = line;
				if (name.size() == 1)
				{
					SingleDeviceParameter<double> *param = new SingleDeviceParameter<double>(name, fullName, 0);
					parameters.push_back(param);
				}
			}
			device = new QuicklimeDispenser(id, nameOfDevice, parameters);
		}
		else if (typeOfDevice == "Sensor")
		{
			std::vector <EnvironmentParameter*> enviromentVariables;
			getline(readFile, line);
			int numOfVariable = stoi(line);
			while (getline(readFile, line))
			{
				std::string name = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string unit = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string min = line.substr(0, line.find(' ', 0));
				removeString(line);
				std::string max = line;
				EnvironmentParameter* param = new EnvironmentParameter(name, unit, stod(min), stod(max));
				enviromentVariables.push_back(param);
			}
			device = new Sensor(id, nameOfDevice, enviromentVariables);
		}
		readFile.close();
	}
	else
		return false;
}
