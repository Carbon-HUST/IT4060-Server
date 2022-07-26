#pragma once
#include "Device.h"
#include "DeviceParameter.h"
#include <chrono>
#include <ctime>
#include <process.h>
#include <Windows.h>
#include "Validation.h"
#include <iostream>


class Pump : public Device
{
public:
	Pump(int id, std::string name, std::vector<DeviceParameter *> parameters);
	bool start();
};