#pragma once

#include "Base/functionBaseManager.h"

class CSetFunction : public CFunctionBase
{
public:
	static CSetFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CSetFunction();
	~CSetFunction() = default;
};
