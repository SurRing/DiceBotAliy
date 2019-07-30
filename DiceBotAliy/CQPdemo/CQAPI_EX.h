#pragma once

#include "stdafx.h"

#include "Unpack.h"

#include "cqp.h"

#include <string>
#include <vector>
#include <map>

namespace CQ {
	// 获取调用api所需的AuthCode
	int getAuthCode();
	//增加运行日志 
	int addLog(int Priorty, const char* Type, const char* Content);

	//发送好友消息
	//Auth=106 失败返回负值,成功返回消息ID 
	int sendPrivateMsg(long long QQ, const char* msg);
	//发送好友消息
	//Auth=106 失败返回负值,成功返回消息ID 
	int sendPrivateMsg(long long QQ, const std::string& msg);

	//发送群消息 
	//Auth=101 失败返回负值,成功返回消息ID
	int sendGroupMsg(long long GroupID, const char* msg);
	//发送群消息 
	//Auth=101 失败返回负值,成功返回消息ID
	int sendGroupMsg(long long GroupID, const std::string& msg);

	//发送讨论组消息 
	//Auth=103 失败返回负值,成功返回消息ID
	int sendDiscussMsg(long long DiscussID, const char* msg);
	//发送讨论组消息 
	//Auth=103 失败返回负值,成功返回消息ID
	int sendDiscussMsg(long long DiscussID, const std::string& msg);

	//取群成员信息
	const char * getGroupMemberInfoV2(int64_t groupid, int64_t QQID, CQBOOL nocache = false);

	//取陌生人信息
	const char * getStrangerInfo(int64_t QQID, CQBOOL nocache = false);

	//置群退出 Auth=127 慎用,此接口需要严格授权 
	int setGroupLeave(
		long long GroupID,
		CQBOOL isDismiss = false // 真/解散本群 (群主) 假/退出本群 (管理、群成员) 
	);
}