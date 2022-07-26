#pragma once
#include "Device.h"
#include "DeviceParameter.h"

class Feeder : public Device
{

public:
	Feeder(int id, std::string name, std::vector<DeviceParameter*> parameters);
};