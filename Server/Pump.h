#pragma once
#include "Device.h"
#include "DeviceParameter.h"


class Pump : public Device
{
public:
	Pump(int id, std::string name, std::vector<DeviceParameter *> parameters);
	
};