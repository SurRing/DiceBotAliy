#include "stdafx.h"

#include "CQAPI_EX.h"
#include "TXTHandler.h"

#include <fstream>

using namespace std;
using namespace CQ;

BlackHandler* BlackHandler::m_Instance = NULL;

BlackHandler::BlackHandler() {
	addLog(CQLOG_DEBUG, "������Ϣ", "����BlackHandler");
}

BlackHandler* BlackHandler::GetInstance() {
	if (m_Instance == NULL) {
		m_Instance = new BlackHandler();
		addLog(CQLOG_DEBUG, "������Ϣ", "��ʼ��BlackHandler");
	}
	return m_Instance;
}

bool BlackHandler::open() {
	addLog(CQLOG_DEBUG, "������Ϣ", "��ʼ��ȡ�������ļ�");
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
	addLog(CQLOG_DEBUG, "������Ϣ", "�������ļ���ȡ���");
	return true;
}

list<int64_t> BlackHandler::openfile(string path) {
	//addLog(CQLOG_DEBUG, "������Ϣ", ("��ʼ��ȡ"+ path).c_str());
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
	//addLog(CQLOG_DEBUG, "������Ϣ", ("������ȡ" + path).c_str());
	return result;
}


void BlackHandler::save() {
	addLog(CQLOG_DEBUG, "������Ϣ", "��ʼ����������ļ�");
	savefile("ExclusionGroup.txt", ExclusionGroup);
	savefile("ExclusionDiscuss.txt", ExclusionDiscuss);
	savefile("ExclusionPrivate.txt", ExclusionPrivate);
	savefile("BlackGroup.txt", BlackGroup);
	savefile("BlackDiscuss.txt", BlackDiscuss);
	savefile("BlackPrivate.txt", BlackPrivate);
	addLog(CQLOG_DEBUG, "������Ϣ", "�������ļ��������");

}
void BlackHandler::savefile(string path, list<int64_t> content) {
	addLog(CQLOG_DEBUG, "������Ϣ", ("��ʼ����"+ path).c_str());
	ofstream  writeFile(path, ios::trunc);
	while (content.size() > 0) {
		writeFile << content.front() << endl;
		content.pop_front();
	}
	writeFile.close();
	addLog(CQLOG_DEBUG, "������Ϣ", (path+"����ɹ�").c_str());
}

bool BlackHandler::contain(list<int64_t> table, int64_t id) {
	//addLog(CQLOG_DEBUG, "������Ϣ", "������");
	if (find(table.begin(), table.end(), id) != table.end()) {
		//addLog(CQLOG_DEBUG, "������Ϣ", "����");
		return true;
	}
	else {
		//addLog(CQLOG_DEBUG, "������Ϣ", "������");
		return false;
	}
}


bool BlackHandler::add(list<int64_t>& table, int64_t id) {
	//addLog(CQLOG_DEBUG, "������Ϣ", ("����" + to_string(id)).c_str());

	if (find(table.begin(), table.end(), id) == table.end()) {
		table.push_back(id);
		//addLog(CQLOG_DEBUG, "������Ϣ", ("�Ѽ���" + to_string(id)).c_str());
		//addLog(CQLOG_DEBUG, "������Ϣ", ("�Ѽ���" + to_string(id)+ "����" + to_string(table.size())).c_str());
		savefile(blackname[&table], table);
		return true;
	}
	else {
		//addLog(CQLOG_DEBUG, "������Ϣ", ("�Ѵ���" + to_string(id)).c_str());
		return false;
	}
}

bool BlackHandler::remove(list<int64_t>& table, int64_t id) {
	table.remove(id);
	savefile(blackname[&table], table);
	return true;
}

list<int64_t> BlackHandler::getTable(list<int64_t>* table) {
	//addLog(CQLOG_DEBUG, "������Ϣ", "��ȡ");
	list<int64_t> new_table = *table;
	//addLog(CQLOG_DEBUG, "������Ϣ", "��ȡ");
	return new_table;
}


SpeakHandler* SpeakHandler::m_Instance = NULL;

SpeakHandler::SpeakHandler() {
	addLog(CQLOG_DEBUG, "������Ϣ", "����SpeakHandler");
}

SpeakHandler* SpeakHandler::GetInstance() {
	if (m_Instance == NULL) {
		m_Instance = new SpeakHandler();
		addLog(CQLOG_DEBUG, "������Ϣ", "��ʼ��SpeakHandler");
	}
	return m_Instance;
}