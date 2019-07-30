#include "stdafx.h"

#include "CQAPI_EX.h"


using namespace CQ;
using namespace std;

int lasterr;

//增加运行日志
int CQ::addLog(const int Priorty, const char* Type, const char* Content)
{
	return lasterr = CQ_addLog(getAuthCode(), Priorty, Type, Content);
}

//发送好友消息
int CQ::sendPrivateMsg(const long long QQ, const char* msg) { return CQ_sendPrivateMsg(getAuthCode(), QQ, msg); }

//发送好友消息
int CQ::sendPrivateMsg(const long long QQ, const std::string& msg) { return sendPrivateMsg(QQ, msg.c_str()); }

//发送群消息
int CQ::sendGroupMsg(const long long GroupID, const char* msg) { return CQ_sendGroupMsg(getAuthCode(), GroupID, msg); }

//发送群消息
int CQ::sendGroupMsg(const long long GroupID, const std::string& msg) { return sendGroupMsg(GroupID, msg.c_str()); }

//发送讨论组消息
int CQ::sendDiscussMsg(const long long DiscussID, const char* msg) { return CQ_sendDiscussMsg(getAuthCode(), DiscussID, msg); }

//发送讨论组消息
int CQ::sendDiscussMsg(const long long DiscussID, const std::string& msg) { return sendDiscussMsg(DiscussID, msg.c_str()); }

//取群成员信息
const char * CQ::getGroupMemberInfoV2(int64_t groupid, int64_t QQID, CQBOOL nocache) { return CQ_getGroupMemberInfoV2(getAuthCode(), groupid, QQID,QQID); }

//取陌生人信息
const char * CQ::getStrangerInfo(int64_t QQID, CQBOOL nocache) { return CQ_getStrangerInfo(getAuthCode(),QQID,nocache); }

//置群退出
int CQ::setGroupLeave(const long long GroupID, const CQBOOL isDismiss){	return lasterr = CQ_setGroupLeave(getAuthCode(), GroupID, isDismiss);}