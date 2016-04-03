#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <thread>
#include <cassert>
#include <csignal>

#include "header/config.hpp"
#include "header/basic.hpp"
#include "header/eventmanager.hpp"

using namespace std;


vector<string> g_vecArgs;
EventManager* g_eventmanager;

bool check_arg_item(char c, string strItem) {
	size_t pos = strItem.find(c);

	return pos != string::npos
			// starts with "-" && not with "--"
			&& string(strItem.begin(), strItem.begin()+1) == "-"
			&& string(strItem.begin(), strItem.begin()+2) != "--";
}
bool check_arg_item(string strText, string strItem) {
	return strItem == "--"+strText;
}
bool check_arg(char c) {
	return any_of(g_vecArgs.begin(), g_vecArgs.end(), [&c](string strItem){
		return check_arg_item(c, strItem);
	});
}
bool check_arg(string strText) {
	assert(strText.length() != 1);

	return any_of(g_vecArgs.begin(), g_vecArgs.end(), [&strText](string strItem){
		return check_arg_item(strText, strItem);
	});
}
string get_arg(char c) {
	string strRet;
	bool bNext = false;

	for(string strItem : g_vecArgs) {
		if(bNext) {
			strRet = strItem;
			break;
		}

		bNext = check_arg_item(c, strItem);
	}

	return strRet;
}
string get_arg(string strText) {
	string strRet;
	bool bNext = false;

	for(string strItem : g_vecArgs) {
		if(bNext) {
			strRet = strItem;
			break;
		}

		bNext = check_arg_item(strText, strItem);
	}

	return strRet;
}

void show_version() {
	cout << PROGNAME << " " << VERSION << endl;
}

void show_help() {
	int indent = 20;

	cout << "usage: " << PROGNAME <<" [option]" << endl << endl
		 << "Options" << endl
		 << "\t" << setw(indent) << left << "-h --help"			<< "Shows this message" << endl
		 << "\t" << setw(indent) << left << "-d --verbose"		<< "Displays events" << endl
		 << "\t" << setw(indent) << left << "-v --version"		<< "Print program version" << endl 
		 << "\t" << setw(indent) << left << "-i --instantly" 	<< "Consume events instantly" << endl
		 << "\t" << setw(indent) << left << "-r --device"		<< "Input device, default: " << endl
		 << "\t" << setw(indent) << left << " "					<< DEV_INPUT << endl
		 << "\t" << setw(indent) << left << "-k --kbpath" 		<< "Path keybindings, default: " << endl
		 << "\t" << setw(indent) << left << " "					<< KEYBINDINGS << endl;
}

void signalHandler(int signum)
{
	cout << "Signal (" << signum << ") received." << endl;

	if(g_eventmanager != nullptr) {
		g_eventmanager->stop();
	}

	exit(signum);
}

int main(int argc, char** argv) {
	/*setuid(0);
	printf("%d\n", getuid());
	system("whoami");
	setuid(1000);
	// NOT root - only root if setuid(0) executed before
	system("whoami");*/

	// TODO !!
	// improvement:
	// check pressed checks subset of bound keys
	// if true at the beginning 
	// & after a key stroke false 
	// -> send all consumed key events

	g_vecArgs = vector<string>(argv+1, argv + argc);
	string strInputDevice = DEV_INPUT;
	string strKbPath = KEYBINDINGS;
	int nFlags = 0;

	// prevent the event consumption after a crash
	signal(SIGTERM, signalHandler);
	signal(SIGSEGV, signalHandler);
	signal(SIGINT, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);

	if(check_arg('h') || check_arg("help")) {
		show_help();
	}
	else if(check_arg('v') || check_arg("version")) {
		show_version();
	}
	else {
		// flags
		if(check_arg('d') || check_arg("verbose")) {
			nFlags |= EV_FLAG_VERBOSE;
		}
		if(check_arg('i') || check_arg("instantly")) {
			nFlags |= EV_FLAG_INSTANTLYCONSUME;
		}

		// input device
		if(check_arg('r')) {
			strInputDevice = get_arg('r');
		}
		else if(check_arg("device")) {
			strInputDevice = get_arg("device");
		}

		// keybindings file
		if(check_arg('k')) {
			strKbPath = get_arg('k');
		}
		else if(check_arg("kbpath")) {
			strKbPath = get_arg("kbpath");
		}

		// fatal errors
		fatal_error(strInputDevice.empty(), "no input device");
		fatal_error(strKbPath.empty(), "no keybindings file");

		g_eventmanager = new EventManager(strInputDevice, strKbPath, nFlags);
		g_eventmanager->process_queue();
		delete g_eventmanager;
		g_eventmanager = nullptr;
	}

	return 0;
}
