#ifndef __LOADER_HPP__
#define __LOADER_HPP__

#include "basic.hpp"
#include "events.hpp"
#include <string>
#include <map>
#include <set>

using namespace std;

string getDirHome();
map<set<ushort>, map<Event, string>> loadKeybindings(string strFile);

#endif
