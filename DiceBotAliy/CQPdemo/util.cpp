

#include "stdafx.h"
#include "util.h"
#include <regex>
#include<string.h>

vector<string> Split(string str, string delim) {
	std::vector<std::string> result;
	if (str.c_str() && strlen(str.c_str()))
	{
		int len = strlen(str.c_str());
		char *src = new char[len + 1];
		strcpy(src, str.c_str());
		src[len] = '\0';
		char *tokenptr = strtok(src, delim.c_str());
		while (tokenptr != NULL)
		{
			std::string tk = tokenptr;
			result.emplace_back(tk);
			tokenptr = strtok(NULL, delim.c_str());
		}
		delete[] src;
	}
	return result;
}