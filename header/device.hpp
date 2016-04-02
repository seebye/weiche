#ifndef __CFILE_H__
#define __CFILE_H__

#include <string>
#include <set>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include "header/basic.hpp"

using namespace std;

class Device {
private:
	int m_nFD;
	bool m_bConsuming;

	//void _ioctl(unsigned long int cmd, ...);

public:
	Device(string strPath, int nFlags);
	~Device();

	// additional device
	void reg_keyboard();

	// events
	void consume();
	void passthrough();
	bool isConsuming();
	struct input_event read();
	void write(ushort type, ushort code, int value);
};

#endif