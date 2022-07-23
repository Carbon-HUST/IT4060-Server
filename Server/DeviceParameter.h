#ifndef DEVICE_PARAMETER_H
#define DEVICE_PARAMETER_H

#include <string>
#include <vector>
#include <typeinfo>
#include "Validation.h"

enum DeviceParameterType 
{
	Single,
	Multiple
};

class DeviceParameter
{
private:
	std::string name;
	std::string fullName;
	DeviceParameterType parameterType;
public:
	DeviceParameter(std::string name, std::string fullName, DeviceParameterType parameterType);
	std::string getName();
	std::string getFullName();
	DeviceParameterType getParameterType();
	virtual bool setValue(std::string value) = 0;
	virtual std::string getValue() = 0; 
	virtual std::string getType() = 0;
};


template <class T>
class SingleDeviceParameter : public DeviceParameter
{
private:
	T value;

public:
	SingleDeviceParameter(std::string name, T value) : DeviceParameter(name, DeviceParameterType::Single), value(value) {};
	bool setValue(std::string value)
	{
		// validate
		// cast string to T
		// assign to value

		switch (typeid(T))
		{
		case typeid(int) :
			int tmp;
			if (isInt(value, tmp))
			{
				value = tmp;
				break;
			}
			else
				return false;

		case typeid(double) :
			double tmp;
			if (isDouble(value, tmp))
			{
				value = tmp;
				break;
			}
			else
				return false;
		
		case typeid(Time) :
			Time tmp;
			if (isTime(value, tmp))
			{
				value = tmp;
				break;
			}
			else
				return false;

		case typeid(TimeRange) :
			TimeRange tmp;
			if (isTimeRange(value, tmp))
			{
				value = tmp;
				break;
			}
			else
				return 0;


		default:
			break;
		}



		return true;
	}

	std::string getValue()
	{
		// cast value to string
		return "value";
	}

	std::string getType()
	{
		return typeid(T).name();
	}
};


template <class T>
class MultipleDeviceParameter : public DeviceParameter
{
private:
	std::vector<T> value;
public:
	MultipleDeviceParameter(std::string name, std::vector<T> value) : DeviceParameter(name, DeviceParameterType::Multiple), value(value) {};

	bool setValue(std::string value)
	{
		// cast string to T
		// push to value
		return true;
	}

	std::string getValue()
	{
		// cast value to string
		return "vector value";
	}

	std::string getType()
	{
		return typeid(T).name();
	}

	bool removeValue(int id)
	{
		if (value.size() <= id)
			return false;
		value.erase(value.begin() + id);
		return true;
	}
};
#endif // !DEVICE_PARAMETER_H
