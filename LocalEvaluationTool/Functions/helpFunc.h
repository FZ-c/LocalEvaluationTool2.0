#pragma once
#include <string>
#include <vector>

#include "Functions/Base/functionBaseManager.h"

class CHelpFunction : public CFunctionBase
{
public:

	static CHelpFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CHelpFunction();
	~CHelpFunction() = default;
};
