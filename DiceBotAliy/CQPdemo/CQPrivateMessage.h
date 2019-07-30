#pragma once

#include "stdafx.h"
#include "CQMessage.h"

class PrivateMessage final : public Message {
public:
	PrivateMessage(int32_t subType, int32_t msgId, int64_t fromQQ, string message, int32_t font);

	int sendMsg(const char*) const override;
	int sendMsg(const std::string&) const override;

	bool ExclusionFilter() override;
	bool BlackFilter() override;

	bool respond() override;
	bool turn() override;
};