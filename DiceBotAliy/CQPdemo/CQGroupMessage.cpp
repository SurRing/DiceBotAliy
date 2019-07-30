#include "stdafx.h"

#include "CQGroupMessage.h"

#include <random>

GroupMessage::GroupMessage(int32_t subType, int32_t msgId, int64_t fromGroup, int64_t fromQQ, string message, int32_t font) :Message(subType, msgId, fromQQ, message, font), fromGroup(fromGroup) {}

int GroupMessage::sendMsg(const char* msg) const { return sendGroupMsg(fromGroup, msg); }
int GroupMessage::sendMsg(const std::string& msg) const { return sendGroupMsg(fromGroup, msg); }

bool GroupMessage::ExclusionFilter() {
	if (Filter(BlackHandler::GetInstance()->ExclusionGroup, fromGroup) && Filter(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ))return true;
	else return false;
}
bool GroupMessage::BlackFilter() {
	if (Filter(BlackHandler::GetInstance()->BlackGroup, fromGroup) && Filter(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ))return true;
	else return false;
}

bool GroupMessage::respond() {
	default_random_engine random_engine;
	LARGE_INTEGER nStartCounter;
	::QueryPerformanceCounter(&nStartCounter);
	random_engine.seed((unsigned)nStartCounter.LowPart);

	smatch m;
	if (message == "��") {
		sendMsg("��~");
	}
	else if (regex_match(message, m, regex("^��ʮ���������(�簲|��)����"))) {
		uniform_int_distribution<unsigned> u(1, 2);
		int re = u(random_engine);
		if (re == 1) {
			sendMsg("�����˼Ҷ�ʮ�滹֪��˵" + m.str(1));
		}
		else if (re == 2) {
			sendMsg("��ʮ�涮��ò��");
		}
		else if (re == 3) {
			sendMsg("������������²ۻ���");
		}
	}
	else if (regex_match(message, m, regex("(aliy|Aliy)"))) {
		sendMsg("����˵��Aliy�ڿ�");
	}
	else if (regex_match(message, m, regex("Ԯ��"))) {
		sendMsg("������绹�ڵĻ�����������ȱǮ��");
	}
	else if (regex_match(message, m, regex("ȱǮ"))) {
		sendMsg("������绹�ڵĻ������������ȱǮ��ȥԮ��");
	}
	return true;

}

bool GroupMessage::turn() {
	if (regex_match(message, turnPattern)) {
		if (message == "/bot on") {
			if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionGroup, fromGroup)) {
				sendMsg("�������ڸ�Ⱥ����");
				addLog(CQLOG_DEBUG, "������Ϣ", ("˽�Ŀ���" + to_string(fromGroup)).c_str());
			}
		}
		if (message == "/bot off") {
			if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionGroup, fromGroup)) {
				sendMsg("�������ڸ�Ⱥ����");
				addLog(CQLOG_DEBUG, "������Ϣ", ("˽�Ĺر�" + to_string(fromGroup)).c_str());
			}
		}
		return true;
	}
	
	return false;
}

bool GroupMessage::Dismiss() {
	if (message == "/Dismiss Aliy") {
		if (fromQQ == 563424794) {
			sendMsg("Aliy����~");
			setGroupLeave(fromGroup, false);
		}
		else {
			sendMsg("��������ʱֻ����Masterʹ�ã���ʹ��/bot off�ر�Aliy");
		}
	}
	
	return false;
}

