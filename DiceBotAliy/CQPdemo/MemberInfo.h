#pragma once

#include <string>

// 陌生人信息
class StrangerInfo final
{
public:
	long long QQID = 0;
	std::string nick = ""; //昵称
	int sex = 255; //0/男性 1/女性 255/未知
	int age = -1; //年龄

	explicit StrangerInfo(const char* msg);
	StrangerInfo() = default;
};