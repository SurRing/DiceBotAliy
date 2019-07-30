#include "stdafx.h"

#include "CQAPI_EX.h"
#include "TXTHandler.h"

#include <fstream>

using namespace std;
using namespace CQ;

BlackHandler* BlackHandler::m_Instance = NULL;

BlackHandler::BlackHandler() {
	addLog(CQLOG_DEBUG, "调试信息", "创建BlackHandler");
}

BlackHandler* BlackHandler::GetInstance() {
	if (m_Instance == NULL) {
		m_Instance = new BlackHandler();
		addLog(CQLOG_DEBUG, "调试信息", "初始化BlackHandler");
	}
	return m_Instance;
}

bool BlackHandler::open() {
	addLog(CQLOG_DEBUG, "调试信息", "开始读取黑名单文件");
	ExclusionGroup = openfile("ExclusionGroup.txt");
	ExclusionDiscuss = openfile("ExclusionDiscuss.txt");
	ExclusionPrivate = openfile("ExclusionPrivate.txt");
	BlackGroup = openfile("BlackGroup.txt");
	BlackDiscuss = openfile("BlackDiscuss.txt");
	BlackPrivate = openfile("BlackPrivate.txt");
	blackname[&ExclusionGroup] = "ExclusionGroup.txt";
	blackname[&ExclusionDiscuss] = "ExclusionDiscuss.txt";
	blackname[&ExclusionPrivate] = "ExclusionPrivate.txt";
	blackname[&BlackGroup] = "BlackGroup.txt";
	blackname[&BlackDiscuss] = "BlackDiscuss.txt";
	blackname[&BlackPrivate] = "BlackPrivate.txt";
	addLog(CQLOG_DEBUG, "调试信息", "黑名单文件读取完成");
	return true;
}

list<int64_t> BlackHandler::openfile(string path) {
	//addLog(CQLOG_DEBUG, "调试信息", ("开始读取"+ path).c_str());
	list<int64_t> result;
	string str;
	ifstream readFile(path);
	if (readFile.is_open()) {
		while (!readFile.eof()) {
			getline(readFile, str);
			if(str!="")result.push_back(stoi(str));
		}
		readFile.close();
	}
	//addLog(CQLOG_DEBUG, "调试信息", ("结束读取" + path).c_str());
	return result;
}


void BlackHandler::save() {
	addLog(CQLOG_DEBUG, "调试信息", "开始保存黑名单文件");
	savefile("ExclusionGroup.txt", ExclusionGroup);
	savefile("ExclusionDiscuss.txt", ExclusionDiscuss);
	savefile("ExclusionPrivate.txt", ExclusionPrivate);
	savefile("BlackGroup.txt", BlackGroup);
	savefile("BlackDiscuss.txt", BlackDiscuss);
	savefile("BlackPrivate.txt", BlackPrivate);
	addLog(CQLOG_DEBUG, "调试信息", "黑名单文件保存完成");

}
void BlackHandler::savefile(string path, list<int64_t> content) {
	addLog(CQLOG_DEBUG, "调试信息", ("开始保存"+ path).c_str());
	ofstream  writeFile(path, ios::trunc);
	while (content.size() > 0) {
		writeFile << content.front() << endl;
		content.pop_front();
	}
	writeFile.close();
	addLog(CQLOG_DEBUG, "调试信息", (path+"保存成功").c_str());
}

bool BlackHandler::contain(list<int64_t> table, int64_t id) {
	//addLog(CQLOG_DEBUG, "调试信息", "检查存在");
	if (find(table.begin(), table.end(), id) != table.end()) {
		//addLog(CQLOG_DEBUG, "调试信息", "存在");
		return true;
	}
	else {
		//addLog(CQLOG_DEBUG, "调试信息", "不存在");
		return false;
	}
}


bool BlackHandler::add(list<int64_t>& table, int64_t id) {
	//addLog(CQLOG_DEBUG, "调试信息", ("加入" + to_string(id)).c_str());

	if (find(table.begin(), table.end(), id) == table.end()) {
		table.push_back(id);
		//addLog(CQLOG_DEBUG, "调试信息", ("已加入" + to_string(id)).c_str());
		//addLog(CQLOG_DEBUG, "调试信息", ("已加入" + to_string(id)+ "共有" + to_string(table.size())).c_str());
		savefile(blackname[&table], table);
		return true;
	}
	else {
		//addLog(CQLOG_DEBUG, "调试信息", ("已存在" + to_string(id)).c_str());
		return false;
	}
}

bool BlackHandler::remove(list<int64_t>& table, int64_t id) {
	table.remove(id);
	savefile(blackname[&table], table);
	return true;
}

list<int64_t> BlackHandler::getTable(list<int64_t>* table) {
	//addLog(CQLOG_DEBUG, "调试信息", "获取");
	list<int64_t> new_table = *table;
	//addLog(CQLOG_DEBUG, "调试信息", "获取");
	return new_table;
}


SpeakHandler* SpeakHandler::m_Instance = NULL;

SpeakHandler::SpeakHandler() {
	addLog(CQLOG_DEBUG, "调试信息", "创建SpeakHandler");
}

SpeakHandler* SpeakHandler::GetInstance() {
	if (m_Instance == NULL) {
		m_Instance = new SpeakHandler();
		addLog(CQLOG_DEBUG, "调试信息", "初始化SpeakHandler");
	}
	return m_Instance;
}