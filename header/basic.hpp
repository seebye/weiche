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


// bug fix 
// delayed executor 
// m_bInterrupted && !m_bInterrupted == true 
// if not repreated long press
// ..
#define BOOL char
#define true 1
#define false 0

milliseconds timestampms();
void sleepms(long lMS);

#endif
