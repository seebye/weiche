#include "header/path.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

string getDirHome() {
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL) {
		homedir = getpwuid(getuid())->pw_dir;
	}

	return homedir;
}