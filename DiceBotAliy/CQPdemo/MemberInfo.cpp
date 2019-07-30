#include "stdafx.h"

#include "MemberInfo.h"

#include "Unpack.h"
#include "CQTools.h"

StrangerInfo::StrangerInfo(const char* msg)
{
	if (msg != nullptr && msg[0] != '\0')
	{
		Unpack p(base64_decode(msg));
		QQID = p.getLong();
		nick = p.getstring();
		sex = p.getInt();
		age = p.getInt();
	}
}