#include "header/loader.hpp"
#include "header/keys.hpp"
#include "header/config.hpp"
#include "jsonxx/jsonxx.h"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace jxx = jsonxx;

#define JXX_KEY_KEYS	"KEYS"

map<set<ushort>, map<Event, string>> loadKeybindings(string strFile) {
	jxx::Array arr;
	map<set<ushort>, map<Event, string>> mapKeybindings;
	stringstream ssContent;
	ifstream is(strFile);
	bool bValidJson;

	ssContent << is.rdbuf();

	bValidJson = arr.parse(ssContent.str());

	fatal_error(!bValidJson, "invalid json");

	for(int i = 0, nLen = arr.size();
		i < nLen;
		i++) {
		if(arr.has<jxx::Object>(i)) {
			map<string, jxx::Value*> mapKV = arr.get<jxx::Object>(i).kv_map();
			set<ushort> setKeys;
			map<Event, string> mapEvents;

			if(mapKV.find(JXX_KEY_KEYS) == mapKV.end()
				|| !mapKV[JXX_KEY_KEYS]->is<jxx::Array>()) {
				cout << "Error["<<i<<":depth 2]: keys missing / wrong type"<<endl;
			}
			else {
				jxx::Array arrKeys = mapKV[JXX_KEY_KEYS]->get<jxx::Array>();

				for(int j = 0, nLen2 = arrKeys.size();
					j < nLen2;
					j++) {

					if(arrKeys.has<jxx::Number>(j)) {
						setKeys.insert(static_cast<ushort>(arrKeys.get<jxx::Number>(j)));
					}
					else if(arrKeys.has<string>(j)) {
						string strKey = arrKeys.get<string>(j);
						KeyCode kc = getKeyCode(strKey);

						if(kc == KEY_UNKNOWN) {
							cout<< "Error["<<i<<":depth 3]: keys item unknown key "<<strKey<<endl;
						}
						else {
							setKeys.insert(kc);
						}
					}
					else {
						cout << "Error["<<i<<":depth 3]: keys item wrong type"<<endl;
					}
				}
			}

			for_each(mapKV.begin(), mapKV.end(), [&i, &mapEvents](pair<string, jxx::Value*> pair) {
				string strKey = pair.first;
				jxx::Value* value = pair.second;
				Event event = getEvent(strKey);

				if(strKey != JXX_KEY_KEYS) {
					if(event == EVENT_UNKNOWN) {
						cout << "Error["<<i<<":depth 2]: unknown event "<<strKey<<endl;
					}
					else if(mapEvents.find(event) != mapEvents.end()) {
						cout << "Error["<<i<<":depth 2]: duplicated event "<<strKey<<endl;
					}
					else {
						if(!value->is<string>()) {
							cout << "Error["<<i<<":depth 2]: invalid value event "<<strKey<<endl;
						}

						mapEvents[event] = value->get<string>();
					}
				}
			});

			if(!setKeys.empty() && !mapEvents.empty()) {
				mapKeybindings[setKeys] = mapEvents;
			}
		}
		else {
			cout << "Error[depth 1]: object expected" << endl;
		}
	}

	return mapKeybindings;
}
