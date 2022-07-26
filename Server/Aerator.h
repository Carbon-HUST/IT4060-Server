#pragma once
#include "DeviceParameter.h"
#include "Device.h"


class Aerator : public Device
{

public:
	Aerator(int id, std::string name, std::vector<DeviceParameter*> parameters);
};