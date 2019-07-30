#include "stdafx.h"

#include "Sender.h"
#include "CQAPI_EX.h"

using namespace CQ;

Sender::Sender()
{
}

int Sender::SendPrivateMsg(int64_t fromQQ, string msg)
{
	return sendPrivateMsg(fromQQ, msg);
}

int Sender::SendGroupMsg(int64_t GroupID, string msg)
{
	return sendGroupMsg(GroupID, msg);
}

int Sender::SendDiscussMsg(int64_t DiscussID, string msg)
{
	return sendDiscussMsg(DiscussID, msg);
}
