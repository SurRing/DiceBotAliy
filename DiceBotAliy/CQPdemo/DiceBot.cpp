#include "stdafx.h"

#include "DiceBot.h"
#include <list>
#include <regex>
#include <ctime>
#include <sys/timeb.h>
#include "util.h"

#include "CQAPI_EX.h"

using namespace CQ;


void ONOFF() {

}

void Help() {

}

void JRRP() {

}

DiceBot::DiceBot() {
	LARGE_INTEGER nFrequency;
	if (::QueryPerformanceFrequency(&nFrequency))
	{
		LARGE_INTEGER nStartCounter;
		::QueryPerformanceCounter(&nStartCounter);
		random_engine.seed((unsigned)nStartCounter.LowPart);
	}
	else // 否则使用当前系统时间初始化随机种子(毫秒级)
	{
		struct timeb stb;
		::ftime(&stb);
		random_engine.seed((unsigned)stb.millitm);
	}
	addLog(CQLOG_DEBUG, "调试信息", "创建DiceBot成功");
}

string DiceBot::HandleDiceCommand(string msg) {
	smatch m;
	regex pattern1("^((([+-])?(([0-9]*d[0-9]*)|([0-9]+)))+)( (.*))?");
	if (regex_search(msg, m, pattern1)) {
		addLog(CQLOG_DEBUG, "调试信息", "骰子指令确认");

		sum = 0;
		return " 投掷" + m.str(7) + " : " + RollMultipleDice(m.str(1));

	}
	else
	{
		return "未知的骰子指令";
	}

}
string DiceBot::RollMultipleDice(string msg) {
	//addLog(CQLOG_DEBUG, "调试信息", "一个骰子");
	string result = "";
	smatch m;
	regex pattern("^([+-])?(([0-9]*d[0-9]*)|([0-9]+))(.*)");
	//addLog(CQLOG_DEBUG, "调试信息", ("msg:" + msg).c_str());

	if (regex_search(msg, m, pattern)) {
		result += m.str(1);
		smatch n;
		string part(m.str(2));
		if (regex_search(part, n, regex("^([0-9]*)d([0-9]*)"))) {
			int a = n.str(1) != "" ? stoi(n.str(1)) : 1;
			int b = n.str(2) != "" ? stoi(n.str(2)) : 100;
			int times = m.str(1) == "-" ? -1 : 1;
			result += GetDice(a, b, times);
		}
		else
		{
			sum += m.str(1) == "-" ? -stoi(part) : stoi(part);

			result += part;
		}
		result += RollMultipleDice(m.str(5));
	}
	else
	{
		result += "="+to_string(sum);
	}
	return result;
}
string DiceBot::GetDice(int a, int b, int times) {
	if(a == 0 || b == 0)return"(不存在的骰子)";
	if (a > 100 || b > 1000)return"(过大的骰子)";
	//addLog(CQLOG_DEBUG, "调试信息", "扔");
	string result;
	uniform_int_distribution<unsigned> u(1, b); //随机数分布对象 
	int re = u(random_engine);
	sum += re*times;
	result += to_string(re);
	for (int j = 1; j < a; j++) {
		re = u(random_engine);
		sum += re*times;
		result += "+"+to_string(re);
	}
	return "("+result+")";
}




string DiceBot::HandleRoleCommand(string msg) {
	smatch m;
	regex pattern1("^([7]?) ([0-9]*)");
	if (regex_search(msg, m, pattern1)) {
		addLog(CQLOG_DEBUG, "调试信息", "人物指令确认");
		string result = " 进行了人体炼成:";
		int v = m.str(1) != "" ? stoi(m.str(1)) : 7;
		int n = m.str(2) != "" ? stoi(m.str(2)) : 1;
		if (n > 10)return " 由于过于贪心，人体炼成失败了。";
		if (v == 7) {
			for (int i = 0; i < n; i++) {
				result += "\n" + RoleMade();
			}
		}
		return result;
	}
	else
	{
		return "未知的人物指令";
	}
}
int DiceBot::RollDice(int a, int b) {
	int sum = 0;
	//addLog(CQLOG_DEBUG, "调试信息", "扔");
	uniform_int_distribution<unsigned> u(1, b); //随机数分布对象 
	sum += u(random_engine);
	for (int j = 1; j < a; j++) {
		sum += u(random_engine);
	}
	return sum;
}
string DiceBot::RoleMade() {
	int sum = 0;
	int re;
	string result = "";

	re = RollDice(3, 6) * 5;
	sum += re;
	result += "力量:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " 体质:" + to_string(re);

	re = RollDice(2, 6) * 5 + 30;
	sum += re;
	result += " 体型:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " 敏捷:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " 外貌:" + to_string(re);

	re = RollDice(2, 6) * 5 + 30;
	sum += re;
	result += " 智力:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " 意志:" + to_string(re);

	re = RollDice(2, 6) * 5 + 30;
	sum += re;
	result += " 教育:" + to_string(re);

	re = RollDice(3, 6) * 5;
	result += " 幸运:" + to_string(re);
	result += " 共计:" + to_string(sum)+"/"+to_string(sum+re);

	return result;
}
