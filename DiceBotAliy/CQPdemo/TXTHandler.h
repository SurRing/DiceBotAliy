#pragma once

#include <string>
#include <list>
#include <map>

using namespace std;

class BlackHandler {
public:
	static BlackHandler* m_Instance;

	static BlackHandler* GetInstance();

	BlackHandler();
	bool open();
	list<int64_t> openfile(string path);
	void save();
	void savefile(string path, list<int64_t> content);


	bool contain(list<int64_t> table, int64_t id);
	bool contain(string table, int64_t id);
	bool add(list<int64_t>& table, int64_t id);
	bool remove(list<int64_t>& table, int64_t id);

	list<int64_t> getTable(list<int64_t>* table);

	map<list<int64_t>*, string> blackname;

	list<int64_t> ExclusionGroup;
	list<int64_t> ExclusionDiscuss;
	list<int64_t> ExclusionPrivate;
	list<int64_t> BlackGroup;
	list<int64_t> BlackDiscuss;
	list<int64_t> BlackPrivate;

};

class SpeakHandler {
	static SpeakHandler* m_Instance;

	static SpeakHandler* GetInstance();

	SpeakHandler();
};
