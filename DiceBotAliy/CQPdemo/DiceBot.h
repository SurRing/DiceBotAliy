#pragma once

#include "stdafx.h"
#include <list>
#include <random>

using namespace std;

void ONOFF();
void Help();
void JRRP();

class DiceBot {
public:
	int sum = 0;
	DiceBot();
	string HandleDiceCommand(string msg);
	string RollMultipleDice(string msg);
	string GetDice(int a, int b, int times=1);
	string HandleRoleCommand(string msg);
	int RollDice(int a, int b);
	string RoleMade();
private:
	default_random_engine random_engine;
};