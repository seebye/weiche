#ifndef __BASIC_HPP__
#define __BASIC_HPP__

#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std::chrono;

#define contains(container, item)		((container).find(item) != (container).end())
#define fatal_error(condition, message)	if(condition) { std::cerr << "error: " << message << endl; exit(EXIT_FAILURE); }

typedef unsigned short ushort;
typedef unsigned int uint;

milliseconds timestampms();
void sleepms(long lMS);

#endif
