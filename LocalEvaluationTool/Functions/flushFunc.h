#pragma once
#include <string>
#include <vector>

#include "Base/functionBaseManager.h"

class CFlushFunction : public CFunctionBase
{
public:

	static CFlushFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CFlushFunction();
	~CFlushFunction() = default;

	int _sign;
};
