#include "stdafx.h"

#include "CQPrivateMessage.h"

PrivateMessage::PrivateMessage(int32_t subType, int32_t msgId, int64_t fromQQ, string message, int32_t font):Message(subType, msgId, fromQQ, message, font){}

int PrivateMessage::sendMsg(const char* msg) const { return sendPrivateMsg(fromQQ, msg); }
int PrivateMessage::sendMsg(const std::string& msg) const { return sendPrivateMsg(fromQQ, msg); }

bool PrivateMessage::ExclusionFilter() {
	if (Message::Filter(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ))return true;
	else return false;
}
bool PrivateMessage::BlackFilter() {
	if (Message::Filter(BlackHandler::GetInstance()->BlackPrivate, fromQQ))return true;
	else return false;
}

bool PrivateMessage::respond() {
	default_random_engine random_engine;
	LARGE_INTEGER nStartCounter;
	::QueryPerformanceCounter(&nStartCounter);
	random_engine.seed((unsigned)nStartCounter.LowPart);


	smatch m;
	if (message == "��") {
		sendMsg("����");
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
	return true;
}

bool PrivateMessage::turn() {
	if (regex_match(message, turnPattern)) {
		if (message == "/bot on") {
			if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ)) {
				sendMsg("�����Ѷ��㿪��");
				addLog(CQLOG_DEBUG, "������Ϣ", ("˽�Ŀ���" + to_string(fromQQ)).c_str());
			}
		}
		if (message == "/bot off") {
			if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ)) {
				sendMsg("�����Ѷ���ر�");
				addLog(CQLOG_DEBUG, "������Ϣ", ("˽�Ĺر�" + to_string(fromQQ)).c_str());
			}
		}
		return true;
	}
	else return false;
}