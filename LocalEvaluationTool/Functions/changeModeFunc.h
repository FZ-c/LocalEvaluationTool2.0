#pragma once
#include <string>
#include <vector>

#include "Base/functionBaseManager.h"

class CChangeModeFunction : public CFunctionBase
{
public:

	static CChangeModeFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CChangeModeFunction();
	~CChangeModeFunction() = default;

	EJudgeType _judgeType;
};
