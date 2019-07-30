#pragma once

#include "stdafx.h"
#include <string>
#include <list>

#include <regex>

#include "CQAPI_EX.h"

#include "TXTHandler.h"
#include "DiceBot.h"
#include "MemberInfo.h"

using namespace std;
using namespace CQ;

static regex HelpPattern("^/help(.*)");
static regex DicePattern("^/r(.*)");
static regex JRRPPattern("^/jrrp");
static regex turnPattern("^/bot(.*)");
static regex cocPattern("^/coc(.*)");


class Message {
public:
	//子类型
	int32_t subType;
	//消息ID
	int32_t msgId;
	//来源QQ
	int64_t fromQQ;
	//消息
	string message;
	//字体
	int32_t font;

	Message(int32_t subType, int32_t msgId, int64_t fromQQ, string message, int32_t font);
	
	virtual int sendMsg(const char*) const = 0;
	virtual int sendMsg(const std::string&) const = 0;

	bool Filter(list<int64_t> table, int64_t targetID) const;
	virtual bool ExclusionFilter() = 0;
	virtual bool BlackFilter() = 0;

	bool dispatch();
	bool RollDice();
	bool RoleMade();
	virtual bool Dismiss();
	bool Help();
	virtual bool other();

	virtual bool respond()=0;
	virtual bool turn()=0;
};