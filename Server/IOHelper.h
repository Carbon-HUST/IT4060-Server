#ifndef IO_HELPER_H
#define IO_HELPER_H

#include <string>
#include "Device.h"

// remove from begin string until meets space(' '). 
std::string removeString(std::string);

bool readDevice(std::string, Device *, std::string);

#endif // !IO_HELPER_H
