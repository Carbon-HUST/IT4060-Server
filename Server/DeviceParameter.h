#ifndef DEVICE_PARAMETER_H
#define DEVICE_PARAMETER_H

#include <string>
#include <vector>
#include <typeinfo>
#include "Validation.h"
#include <utility>

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
	SingleDeviceParameter(std::string name, std::string fullName, T value) : DeviceParameter(name, fullName, DeviceParameterType::Single), value(value) {};
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
				this->value = tmp;
				break;
			}
			else
				return false;

		case typeid(double) :
			double tmp;
			if (isDouble(value, tmp))
			{
				this->value = tmp;
				break;
			}
			else
				return false;
		
		case typeid(Time) :
			Time tmp;
			if (isTime(value, tmp))
			{
				this->value = tmp;
				break;
			}
			else
				return false;

		case typeid(TimeRange) :
			TimeRange tmp;
			if (isTimeRange(value, tmp))
			{
				this->value = tmp;
				break;
			}
			else
				return false;

		default:
			return false;
		}

		return true;
	}

	std::string getValue()
	{
		// cast value to string and return.

		std::string retValue;
		if (typeid(value) == typeid(int) || typeid(value) == typeid(double))
			retValue = std::to_string(value);
		else if (typeid(value) == typeid(Time))
			retValue = std::to_string(value.hour) + ':' + std::to_string(value.minute) + ':' + std::to_string(value.second);
		else if (typeid(value) == typeid(TimeRange))
		{
			// HH:mm:ss#HH:mm:ss
			retValue = std::to_string(value.start.hour) + ':' + std::to_string(value.start.minute) + ':' + std::to_string(value.start.second)
						+ '#' + std::to_string(value.end.hour) + std::to_string(value.end.minute) + std::to_string(value.end.second);
		}
			
		// cast value to string
		return retValue;
	}

	std::string getType()
	{
		return typeid(T).name();
	}

	//get parameter (real value in memory)
	T getParameter()
	{
		return this->value;
	}

};


template <class T>
class MultipleDeviceParameter : public DeviceParameter
{
private:
	std::vector<std::pair<int, T>> values;
public:
	MultipleDeviceParameter(std::string name, std::string fullName, std::vector<T> values) : DeviceParameter(name, std::string fullName, DeviceParameterType::Multiple), values(values) {};

	bool setValue(std::string value)
	{
		// when add, check id of the last elem of the vector, add 1 to said id
		// cast string to T
		// push to value

		int id;
		if (values.size() == 0)
			id = 1;
		else
			id = values.back().first + 1;

		switch (typeid(T))
		{
		case typeid(int) :
			int tmp;
			if (isInt(value, tmp))
			{
				values.push_back({ id,tmp });
				break;
			}
			else
				return false;

		case typeid(double) :
			double tmp;
			if (isDouble(value, tmp))
			{
				values.push_back({ id, tmp });
				break;
			}
			else
				return false;

		case typeid(Time) :
			Time tmp;
			if (isTime(value, tmp))
			{
				values.push_back({id, tmp});
				break;
			}
			else
				return false;

		case typeid(TimeRange) :
			TimeRange tmp;
			if (isTimeRange(value, tmp))
			{
				values.push_back({id, tmp});
				break;
			}
			else
				return false;

		default:
			return false;
		}
		return true;
	}

	std::string getValue()
	{
	// id#value id#value id#value
		std::string strVals = "";
		if (values.size() == 0)
			return strVals;
		else
		{
			for (auto v : values)
			{
				if (typeid(v.second) == typeid(int) || typeid(v.second) == typeid(double))
				{
					strVals += std::to_string(v.first) + '#' + std::to_string(v.second);
					strVals += ' ';
				}
				else if (typeid(v.second) == typeid(Time))
				{
					// id#HH:mm:ss id#HH:mm:ss
					strVals += std::to_string(v.first) + '#' + std::to_string(v.second.hour) + ':' + std::to_string(v.second.minute) + ':' + std::to_string(v.second.second);
					strVals += ' ';
				}
				else if (typeid(v.second) == typeid(TimeRange))
				{
					//id#HH:mm:ss#HH:mm:ss id#HH:mm:ss#HH:mm:ss
					strVals += std::to_string(v.first) + '#' + std::to_string(v.second.start.hour) + ':'
						+ std::to_string(v.second.start.minute) + ':'
						+ std::to_string(v.second.start.second) + '#'
						+std::to_string(v.second.end.hour) + ':'
						+ std::to_string(v.second.end.minute) + ':'
						+ std::to_string(v.second.end.second);
					
					strVals += ' ';
																
				}

			}
			return strVals;
		}
			
	}

	std::string getType()
	{
		return typeid(T).name();
	}

	bool removeValue(int id)
	{
		for (int i = 0; i < value.size(); i++)
		{
			if (values[i].first == id)
			{
				values.erase(i);
				return true;
			}
		}
		return false;
	}

	//get parameter (real value in memory)
	std::vector<int, T> getParameters()
	{
		return this->values;
	}

};
#endif // !DEVICE_PARAMETER_H
