#include "stdafx.h"

#include "CQAPI_EX.h"
#include "CommandDispatcher.h"
#include "MemberInfo.h"

#include "DiceBot.h"
#include "Sender.h"
#include "TXTHandler.h"

#include "cqp.h"

#include <regex>


using namespace CQ;

Sender sender;

CommandDispatcher::CommandDispatcher()
{
	BlacktxtHandler = BlackHandler::GetInstance();
	addLog(CQLOG_DEBUG, "调试信息", "创建CommandDispatcher成功");
}

bool CommandDispatcher::Filter(list<int64_t> table, int64_t targetID) {
	if (!BlacktxtHandler->contain(table, targetID))return true;
	else return false;
}

#pragma region Filter
bool CommandDispatcher::GroupFilter(GroupMessage msg)
{
	if (Filter(BlackHandler::GetInstance()->BlackGroup, msg.fromGroup) && Filter(BlackHandler::GetInstance()->BlackPrivate, msg.fromQQ)) {
		//addLog(CQLOG_DEBUG, "调试信息", "过滤成功");
		return true;
	}
	else return false;
}
bool CommandDispatcher::DiscussFilter(DiscussMessage msg)
{
	if (Filter(BlackHandler::GetInstance()->BlackDiscuss, msg.fromDiscuss) && Filter(BlackHandler::GetInstance()->BlackPrivate, msg.fromQQ))return true;
	else return false;
}
bool CommandDispatcher::PrivateFilter(PrivateMessage msg)
{
	if (Filter(BlackHandler::GetInstance()->BlackPrivate, msg.fromQQ)) {
		//addLog(CQLOG_DEBUG, "调试信息", "过滤成功");
		return true;
	}
	else return false;
}
bool CommandDispatcher::GroupOffFilter(GroupMessage msg) {
	if (Filter(BlackHandler::GetInstance()->ExclusionGroup, msg.fromGroup) && Filter(BlackHandler::GetInstance()->ExclusionPrivate, msg.fromQQ))return true;
	else return false;
}
bool CommandDispatcher::DiscussOffFilter(DiscussMessage msg) {
	if (Filter(BlackHandler::GetInstance()->ExclusionDiscuss, msg.fromDiscuss) && Filter(BlackHandler::GetInstance()->ExclusionPrivate, msg.fromQQ))return true;
	else return false;
}
bool CommandDispatcher::PrivateOffFilter(PrivateMessage msg) {
	if (Filter(BlackHandler::GetInstance()->ExclusionPrivate, msg.fromQQ))return true;
	else return false;
}
#pragma endregion

bool CommandDispatcher::deal(Message* msg) {
	regex HelpPattern("^/help(.*)");
	regex DicePattern("^/r(.*)");
	regex JRRPPattern ("^/jrrp");

	smatch m;
	if (regex_search(msg->message, m, DicePattern)) {
		/*
		if (random_engine_list.empty()) {
			default_random_engine e;
			e.seed(ctime);
			random_engine_list.push_back(e);
		}*/
		DiceBot diceBot;
		string response = diceBot.HandleDiceCommand(m.str(1));
		response.insert(0, StrangerInfo(getStrangerInfo(msg->fromQQ)).nick);
		msg->sendMsg("* "+response);
	}
	else {

		addLog(CQLOG_DEBUG, "调试信息", "未处理的信息");
	}
	return true;
}

bool CommandDispatcher::turn(int32_t Type, Message* msg, int64_t targetID) {
	regex turnPattern("^/bot(.*)");
	if (regex_match(msg->message, turnPattern)) {
		addLog(CQLOG_DEBUG, "调试信息", ("类型" + to_string(Type)).c_str());
		if (msg->message == "/bot on") {
			if (Type == 21) {
				if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionPrivate, targetID)) {
					msg->sendMsg("骰子已对你开放");
					addLog(CQLOG_DEBUG, "调试信息", ("私聊开启" + to_string(targetID)).c_str());
				}
			}
			else if (Type == 2) {
				if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionGroup, targetID)) {
					msg->sendMsg("骰子已在该群开启");
					addLog(CQLOG_DEBUG, "调试信息", ("群聊开启" + to_string(targetID)).c_str());
				}
			}
			else if (Type == 4) {
				if (BlackHandler::GetInstance()->remove(BlackHandler::GetInstance()->ExclusionDiscuss, targetID)) {
					msg->sendMsg("骰子已在该讨论组开启");
					addLog(CQLOG_DEBUG, "调试信息", ("讨论组开启" + to_string(targetID)).c_str());
				}
			}
			else {
				addLog(CQLOG_DEBUG, "调试信息", ("错误类型" + to_string(Type)).c_str());

			}
		}
		if (msg->message == "/bot off") {
			if (Type == 21) {
				if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionPrivate, targetID)) {
					msg->sendMsg("骰子已对你关闭");
					addLog(CQLOG_DEBUG, "调试信息", ("私聊关闭" + to_string(targetID)).c_str());
				}
			}
			else if (Type == 2) {
				if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionGroup, targetID)) {
					msg->sendMsg("骰子已在该群禁用");
					addLog(CQLOG_DEBUG, "调试信息", ("群聊关闭" + to_string(targetID)).c_str());
				}
			}
			else if (Type == 4) {
				if (BlackHandler::GetInstance()->add(BlackHandler::GetInstance()->ExclusionDiscuss, targetID)) {
					msg->sendMsg("骰子已在该讨论组禁用");
					addLog(CQLOG_DEBUG, "调试信息", ("讨论组关闭" + to_string(targetID)).c_str());
				}
			}
			else {
				addLog(CQLOG_DEBUG, "调试信息", ("错误类型"+to_string(Type)).c_str());
			}
		}
	}
}