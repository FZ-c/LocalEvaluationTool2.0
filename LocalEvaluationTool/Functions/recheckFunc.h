#pragma once
#include <string>
#include <vector>

#include "Base/functionBaseManager.h"

class CRecheckFunction : public CFunctionBase
{
public:

	static CRecheckFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CRecheckFunction();
	~CRecheckFunction() = default;
};
