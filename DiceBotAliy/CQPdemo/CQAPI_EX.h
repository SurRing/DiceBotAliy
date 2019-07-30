#pragma once

#include "stdafx.h"

#include "Unpack.h"

#include "cqp.h"

#include <string>
#include <vector>
#include <map>

namespace CQ {
	// ��ȡ����api�����AuthCode
	int getAuthCode();
	//����������־ 
	int addLog(int Priorty, const char* Type, const char* Content);

	//���ͺ�����Ϣ
	//Auth=106 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID 
	int sendPrivateMsg(long long QQ, const char* msg);
	//���ͺ�����Ϣ
	//Auth=106 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID 
	int sendPrivateMsg(long long QQ, const std::string& msg);

	//����Ⱥ��Ϣ 
	//Auth=101 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int sendGroupMsg(long long GroupID, const char* msg);
	//����Ⱥ��Ϣ 
	//Auth=101 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int sendGroupMsg(long long GroupID, const std::string& msg);

	//������������Ϣ 
	//Auth=103 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int sendDiscussMsg(long long DiscussID, const char* msg);
	//������������Ϣ 
	//Auth=103 ʧ�ܷ��ظ�ֵ,�ɹ�������ϢID
	int sendDiscussMsg(long long DiscussID, const std::string& msg);

	//ȡȺ��Ա��Ϣ
	const char * getGroupMemberInfoV2(int64_t groupid, int64_t QQID, CQBOOL nocache = false);

	//ȡİ������Ϣ
	const char * getStrangerInfo(int64_t QQID, CQBOOL nocache = false);

	//��Ⱥ�˳� Auth=127 ����,�˽ӿ���Ҫ�ϸ���Ȩ 
	int setGroupLeave(
		long long GroupID,
		CQBOOL isDismiss = false // ��/��ɢ��Ⱥ (Ⱥ��) ��/�˳���Ⱥ (����Ⱥ��Ա) 
	);
}