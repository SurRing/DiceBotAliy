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
	if (message == "晚安") {
		sendMsg("安安");
	}
	else if (regex_match(message, m, regex("^二十面是无情的(早安|晚安)机器"))) {
		uniform_int_distribution<unsigned> u(1, 2);
		int re = u(random_engine);
		if (re == 1) {
			sendMsg("至少人家二十面还知道说" + m.str(1));
		}
		else if (re == 2) {
			sendMsg("二十面懂礼貌嘛");
		}
		else if (re == 3) {
			sendMsg("你则是无情的吐槽机器");
		}
	}
	return true;
}

bool PrivateMessage::turn() {
	if (regex_match(message, turnPattern)) {
		if (message == "/bot on") {
			if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ)) {
				sendMsg("骰子已对你开放");
				addLog(CQLOG_DEBUG, "调试信息", ("私聊开启" + to_string(fromQQ)).c_str());
			}
		}
		if (message == "/bot off") {
			if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ)) {
				sendMsg("骰子已对你关闭");
				addLog(CQLOG_DEBUG, "调试信息", ("私聊关闭" + to_string(fromQQ)).c_str());
			}
		}
		return true;
	}
	else return false;
}