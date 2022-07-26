#pragma once
#include "DeviceParameter.h"
#include "Device.h"
#include <chrono>
#include <ctime>
#include <process.h>
#include <Windows.h>
#include <iostream>

class Aerator : public Device
{

public:
	Aerator(int id, std::string name, std::vector<DeviceParameter*> parameters);
	bool getTimeRanges();
	bool start();
};