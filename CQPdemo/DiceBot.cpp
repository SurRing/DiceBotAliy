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
	else // ����ʹ�õ�ǰϵͳʱ���ʼ���������(���뼶)
	{
		struct timeb stb;
		::ftime(&stb);
		random_engine.seed((unsigned)stb.millitm);
	}
	addLog(CQLOG_DEBUG, "������Ϣ", "����DiceBot�ɹ�");
}

string DiceBot::HandleDiceCommand(string msg) {
	smatch m;
	regex pattern1("^((([+-])?(([0-9]*d[0-9]*)|([0-9]+)))+)( (.*))?");
	if (regex_search(msg, m, pattern1)) {
		addLog(CQLOG_DEBUG, "������Ϣ", "����ָ��ȷ��");

		sum = 0;
		return " Ͷ��" + m.str(7) + " : " + RollMultipleDice(m.str(1));

	}
	else
	{
		return "δ֪������ָ��";
	}

}
string DiceBot::RollMultipleDice(string msg) {
	//addLog(CQLOG_DEBUG, "������Ϣ", "һ������");
	string result = "";
	smatch m;
	regex pattern("^([+-])?(([0-9]*d[0-9]*)|([0-9]+))(.*)");
	//addLog(CQLOG_DEBUG, "������Ϣ", ("msg:" + msg).c_str());

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
	if(a == 0 || b == 0)return"(�����ڵ�����)";
	if (a > 100 || b > 1000)return"(���������)";
	//addLog(CQLOG_DEBUG, "������Ϣ", "��");
	string result;
	uniform_int_distribution<unsigned> u(1, b); //������ֲ����� 
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
		addLog(CQLOG_DEBUG, "������Ϣ", "����ָ��ȷ��");
		string result = " ��������������:";
		int v = m.str(1) != "" ? stoi(m.str(1)) : 7;
		int n = m.str(2) != "" ? stoi(m.str(2)) : 1;
		if (n > 10)return " ���ڹ���̰�ģ���������ʧ���ˡ�";
		if (v == 7) {
			for (int i = 0; i < n; i++) {
				result += "\n" + RoleMade();
			}
		}
		return result;
	}
	else
	{
		return "δ֪������ָ��";
	}
}
int DiceBot::RollDice(int a, int b) {
	int sum = 0;
	//addLog(CQLOG_DEBUG, "������Ϣ", "��");
	uniform_int_distribution<unsigned> u(1, b); //������ֲ����� 
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
	result += "����:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " ����:" + to_string(re);

	re = RollDice(2, 6) * 5 + 30;
	sum += re;
	result += " ����:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " ����:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " ��ò:" + to_string(re);

	re = RollDice(2, 6) * 5 + 30;
	sum += re;
	result += " ����:" + to_string(re);

	re = RollDice(3, 6) * 5;
	sum += re;
	result += " ��־:" + to_string(re);

	re = RollDice(2, 6) * 5 + 30;
	sum += re;
	result += " ����:" + to_string(re);

	re = RollDice(3, 6) * 5;
	result += " ����:" + to_string(re);
	result += " ����:" + to_string(sum)+"/"+to_string(sum+re);

	return result;
}
