#include "stdafx.h"

#include "CQAPI_EX.h"


using namespace CQ;
using namespace std;

int lasterr;

//����������־
int CQ::addLog(const int Priorty, const char* Type, const char* Content)
{
	return lasterr = CQ_addLog(getAuthCode(), Priorty, Type, Content);
}

//���ͺ�����Ϣ
int CQ::sendPrivateMsg(const long long QQ, const char* msg) { return CQ_sendPrivateMsg(getAuthCode(), QQ, msg); }

//���ͺ�����Ϣ
int CQ::sendPrivateMsg(const long long QQ, const std::string& msg) { return sendPrivateMsg(QQ, msg.c_str()); }

//����Ⱥ��Ϣ
int CQ::sendGroupMsg(const long long GroupID, const char* msg) { return CQ_sendGroupMsg(getAuthCode(), GroupID, msg); }

//����Ⱥ��Ϣ
int CQ::sendGroupMsg(const long long GroupID, const std::string& msg) { return sendGroupMsg(GroupID, msg.c_str()); }

//������������Ϣ
int CQ::sendDiscussMsg(const long long DiscussID, const char* msg) { return CQ_sendDiscussMsg(getAuthCode(), DiscussID, msg); }

//������������Ϣ
int CQ::sendDiscussMsg(const long long DiscussID, const std::string& msg) { return sendDiscussMsg(DiscussID, msg.c_str()); }

//ȡȺ��Ա��Ϣ
const char * CQ::getGroupMemberInfoV2(int64_t groupid, int64_t QQID, CQBOOL nocache) { return CQ_getGroupMemberInfoV2(getAuthCode(), groupid, QQID,QQID); }

//ȡİ������Ϣ
const char * CQ::getStrangerInfo(int64_t QQID, CQBOOL nocache) { return CQ_getStrangerInfo(getAuthCode(),QQID,nocache); }

//��Ⱥ�˳�
int CQ::setGroupLeave(const long long GroupID, const CQBOOL isDismiss){	return lasterr = CQ_setGroupLeave(getAuthCode(), GroupID, isDismiss);}