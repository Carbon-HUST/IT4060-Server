#pragma once
#include "Device.h"
#include "DeviceParameter.h"

class QuicklimeDispenser : public Device
{
public:
	QuicklimeDispenser(int id, std::string name, std::vector<DeviceParameter> parameters);
};