#include "stdafx.h"

#include "CQDiscussMessage.h"

DiscussMessage::DiscussMessage(int32_t subType, int32_t msgId, int64_t fromDiscuss, int64_t fromQQ, string message, int32_t font) :Message(subType, msgId, fromQQ, message, font), fromDiscuss(fromDiscuss) {}

int DiscussMessage::sendMsg(const char* msg) const { return sendDiscussMsg(fromDiscuss, msg); }
int DiscussMessage::sendMsg(const std::string& msg) const { return sendDiscussMsg(fromDiscuss, msg); }

bool DiscussMessage::ExclusionFilter() {
	if (Filter(BlackHandler::GetInstance()->ExclusionDiscuss, fromDiscuss) && Filter(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ))return true;
	else return false;
}
bool DiscussMessage::BlackFilter() {
	if (Filter(BlackHandler::GetInstance()->BlackDiscuss, fromDiscuss) && Filter(BlackHandler::GetInstance()->ExclusionPrivate, fromQQ))return true;
	else return false;
}

bool DiscussMessage::respond() {
	return true;
}

bool DiscussMessage::turn() {
	if (regex_match(message, turnPattern)) {
		if (message == "/bot on") {
			if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionDiscuss, fromDiscuss)) {
				sendMsg("骰子已在该讨论组开启");
				addLog(CQLOG_DEBUG, "调试信息", ("私聊开启" + to_string(fromDiscuss)).c_str());
			}
		}
		if (message == "/bot off") {
			if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionDiscuss, fromDiscuss)) {
				sendMsg("骰子已在该讨论组禁用");
				addLog(CQLOG_DEBUG, "调试信息", ("私聊关闭" + to_string(fromDiscuss)).c_str());
			}
		}
		return true;
	}
	
	return false;
}