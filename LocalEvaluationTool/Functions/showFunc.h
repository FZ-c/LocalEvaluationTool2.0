#pragma once
#include <string>
#include <vector>

#include "Functions/Base/functionBaseManager.h"

class CShowFunction : public CFunctionBase
{
public:

	static CShowFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CShowFunction();
	~CShowFunction() = default;

	int _sign;
};
