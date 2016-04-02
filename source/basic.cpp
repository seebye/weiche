#include "header/basic.hpp"
#include <thread>

using namespace std;

milliseconds timestampms() {
	return duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
}

void sleepms(long lMS) {
	this_thread::sleep_for(milliseconds{lMS});
}
