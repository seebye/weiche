#include "header/device.hpp"
#include "header/basic.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <linux/uinput.h>
#include <iostream>
#include <stdarg.h>

extern "C" int c_open(const char *path, int oflag) {
	return open(path, oflag);
}
void c_ioctl(int fd, unsigned long int cmd) {
	int nRet = ioctl(fd, cmd);
	fatal_error(nRet < 0, "ioctl0");
}
void c_ioctl(int fd, unsigned long int cmd, unsigned long int val) {
	int nRet = ioctl(fd, cmd, val);
	fatal_error(nRet < 0, "ioctl1");
}

extern "C" ssize_t c_write(int fd, const void *buf, size_t count) {
	return write(fd, buf, count);
}

extern "C" ssize_t c_read(int fd, void *buf, size_t count) {
	return read(fd, buf, count);
}

Device::Device(string strPath, int nFlags)
	: m_nFD(0), m_bConsuming(false) {
	const char* pcIn = strPath.c_str();
	m_nFD = c_open(pcIn, nFlags);

	fatal_error(m_nFD < 0, "open");
}

Device::~Device() {
	passthrough();
	close(m_nFD);
}

bool Device::isConsuming() {
	return m_bConsuming;
}

void Device::reg_keyboard() {
	struct uinput_user_dev uidev;
	ssize_t bytes;

	c_ioctl(m_nFD, UI_SET_EVBIT, EV_SYN);
	c_ioctl(m_nFD, UI_SET_EVBIT, EV_KEY);
	c_ioctl(m_nFD, UI_SET_EVBIT, EV_MSC);

	for(int i = 0; i < KEY_MAX; ++i) {
		c_ioctl(m_nFD, UI_SET_KEYBIT, i);
	}

	memset(&uidev, 0, sizeof(uidev));
	strcpy(uidev.name, "weiche");
	uidev.id.bustype = BUS_USB;
	uidev.id.vendor  = 1;
	uidev.id.product = 1;
	uidev.id.version = 1;

	bytes = c_write(m_nFD, &uidev, sizeof(uidev));
	fatal_error(bytes < 0, "write");

	c_ioctl(m_nFD, UI_DEV_CREATE);
}

void Device::consume() {
	if(!m_bConsuming) {
		c_ioctl(m_nFD, EVIOCGRAB, 1);
	}

	m_bConsuming = true;
}

void Device::passthrough() {
	if(m_bConsuming) {
		c_ioctl(m_nFD, EVIOCGRAB, 0);
	}

	m_bConsuming = false;
}

struct input_event Device::read() {
	struct input_event event;
	ssize_t bytes;

	bytes = c_read(m_nFD, &event, sizeof(struct input_event));
	fatal_error(bytes < 0, "read");

	return event;
}

void Device::write(ushort type, ushort code, int value) {
	struct input_event event;
	ssize_t bytes;

	memset(&event, 0, sizeof(event));
	event.type = type;
	event.code = code;
	event.value = value;

	bytes = c_write(m_nFD, &event, sizeof(event));
	fatal_error(bytes != sizeof(event), "on send_event");
}