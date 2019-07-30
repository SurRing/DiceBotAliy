#pragma once

#include <string>
using namespace std;

class Sender {
public:
	Sender();
	int SendPrivateMsg(int64_t fromQQ, string msg);
	int SendGroupMsg(int64_t GroupID, string msg);
	int SendDiscussMsg(int64_t DiscussID, string msg);
};