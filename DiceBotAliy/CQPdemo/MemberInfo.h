#pragma once

#include <string>

// İ������Ϣ
class StrangerInfo final
{
public:
	long long QQID = 0;
	std::string nick = ""; //�ǳ�
	int sex = 255; //0/���� 1/Ů�� 255/δ֪
	int age = -1; //����

	explicit StrangerInfo(const char* msg);
	StrangerInfo() = default;
};