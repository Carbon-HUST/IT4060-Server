#include "Aerator.h"

Aerator::Aerator(int id, std::string name, std::vector<DeviceParameter*> parameters) : Device(id, name, parameters)
{
	// aerator has 2 parameter: C (fan speed) and a vector of timerange
	SingleDeviceParameter<double> *fanSpeed = new SingleDeviceParameter<double>("C", "Fan Speed", 1000);

	std::vector<TimeRange> trs;
	MultipleDeviceParameter<TimeRange> *timeRanges = new MultipleDeviceParameter<TimeRange>("TR", "Time ranges", trs);

	this->addParameter(fanSpeed);
	this->addParameter(timeRanges);
}

bool Aerator::getTimeRanges()
{
	return false;
}

bool Aerator::start()
{
	return false;
}


unsigned _stdcall AeratorThread(void *params)
{
	Aerator* aerator = (Aerator*)params;
	DeviceParameter *parameters = aerator->getParameterReference("TR");
	MultipleDeviceParameter<TimeRange> *timeRanges = (MultipleDeviceParameter<TimeRange>*) parameters;
	std::vector<int, TimeRange> aeratorOnTimeRanges = timeRanges->getParameters();

	int command; // to check if client forces device to turn off
	while (true)
	{	

		if (aerator->getStatus() == true)
		{
			std::cout << "Aerator is ON, Fan speed " << aerator->getParameter("C") << std::endl;
			while (aerator->getStatus() == true)
			{
				if (aerator->getStatus() == false)
				{
					std::cout << "Aerator is OFF" << std::endl;
					break;
				}
			}
		}

		for (auto tr : aeratorOnTimeRanges)
		{
			command = 0;
			std::time_t nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			struct tm nowTm;
			localtime_s(&nowTm, &nowTime);
			Time t = Time(nowTm.tm_hour, nowTm.tm_min, nowTm.tm_sec);
			if (t > tr.second.start && t < tr.second.end)
			{
				if(aerator->setStatus(true))
					std::cout << "Aerator is ON, Fan speed " << aerator->getParameter("C") << std::endl;
				while (t > tr.second.start && t < tr.second.end)
				{
					nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
					localtime_s(&nowTm, &nowTime);
					t = Time(nowTm.tm_hour, nowTm.tm_min, nowTm.tm_sec);
					
					if (command == 1) continue;
					
					if (aerator->getStatus() == false)
					{
						command = 1;
						std::cout << "Aerator is OFF" << std::endl;
					}	
				}
				if (aerator->setStatus(false) && aerator->getStatus() != false)
					std::cout << "Aerator id OFF" << std::endl;
			}
		}
	}
}
