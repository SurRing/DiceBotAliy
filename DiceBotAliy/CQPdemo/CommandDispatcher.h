#pragma once

#include "stdafx.h"
#include "TXTHandler.h"
#include <string>
#include <random>
#include <list>

#include "CQPrivateMessage.h"
#include "CQGroupMessage.h"
#include "CQDiscussMessage.h"

using namespace std;

class CommandDispatcher {
public:
	CommandDispatcher();
	bool GroupFilter(GroupMessage msg);
	bool DiscussFilter(DiscussMessage msg);
	bool PrivateFilter(PrivateMessage msg);
	bool GroupOffFilter(GroupMessage msg);
	bool DiscussOffFilter(DiscussMessage msg);
	bool PrivateOffFilter(PrivateMessage msg);
	bool Filter(list<int64_t> table, int64_t targetID);
	bool Filter(string table, int64_t targetID);

	BlackHandler* BlacktxtHandler;
	bool deal(Message* msg);
	bool turn(int32_t subType, Message* msg, int64_t targetID);
	bool send(int32_t subType, int64_t fromQQ, string msg);
};