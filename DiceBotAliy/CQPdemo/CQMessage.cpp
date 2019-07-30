#include "stdafx.h"

#include "CQMessage.h"

#include "Help.h"

Message::Message(int32_t subType, int32_t msgId, int64_t fromQQ, string message, int32_t font) :subType(subType), msgId(msgId), fromQQ(fromQQ), message(message), font(font) {}

bool Message::Filter(list<int64_t> table, int64_t targetID) const {
	if (!BlackHandler::GetInstance()->contain(table, targetID))return true;
	else return false;
}

bool Message::dispatch() {
	if (!BlackFilter())return true;
	if (ExclusionFilter()) {
		if (RoleMade()) {}
		if (Dismiss()) {}
		if (Help()) {}
		if (RollDice()) {}
		respond();
		other();
	}
	turn();
}

bool Message::RollDice() {
	smatch m;
	if (regex_search(message, m, DicePattern)) {
		DiceBot diceBot;
		string response = diceBot.HandleDiceCommand(m.str(1));
		sendMsg("* " + StrangerInfo(getStrangerInfo(fromQQ)).nick + response);
		return true;
	}
	
	return false;
}

bool Message::RoleMade() {
	smatch m;
	if (regex_search(message, m, cocPattern)) {
		DiceBot diceBot;
		string response = diceBot.HandleRoleCommand(m.str(1));
		sendMsg("* " + StrangerInfo(getStrangerInfo(fromQQ)).nick + response);
		return true;
	}
	
	return false;
}

bool Message::Dismiss() {
	return false;

}

bool Message::other() {
	return false;
}

bool Message::Help() {
	smatch m;
	if (message == "/help") {
		sendMsg(help);
		return true;
	}

	return false;
}