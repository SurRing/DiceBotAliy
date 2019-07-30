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
	if (message == "晚安") {
		sendMsg("眠~");
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
	else if (regex_match(message, m, regex("(aliy|Aliy)"))) {
		sendMsg("你在说，Aliy在看");
	}
	else if (regex_match(message, m, regex("援交"))) {
		sendMsg("如果早苗还在的话，她会问你缺钱吗");
	}
	else if (regex_match(message, m, regex("缺钱"))) {
		sendMsg("如果早苗还在的话，她会告诉你缺钱就去援交");
	}
	return true;

}

bool GroupMessage::turn() {
	if (regex_match(message, turnPattern)) {
		if (message == "/bot on") {
			if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionGroup, fromGroup)) {
				sendMsg("骰子已在该群开启");
				addLog(CQLOG_DEBUG, "调试信息", ("私聊开启" + to_string(fromGroup)).c_str());
			}
		}
		if (message == "/bot off") {
			if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionGroup, fromGroup)) {
				sendMsg("骰子已在该群禁用");
				addLog(CQLOG_DEBUG, "调试信息", ("私聊关闭" + to_string(fromGroup)).c_str());
			}
		}
		return true;
	}
	
	return false;
}

bool GroupMessage::Dismiss() {
	if (message == "/Dismiss Aliy") {
		if (fromQQ == 563424794) {
			sendMsg("Aliy走啦~");
			setGroupLeave(fromGroup, false);
		}
		else {
			sendMsg("该命令暂时只能由Master使用，请使用/bot off关闭Aliy");
		}
	}
	
	return false;
}

