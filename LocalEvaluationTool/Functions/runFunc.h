#pragma once
#include <string>
#include <vector>

#include "Base/functionBaseManager.h"

class CRunFunction : public CFunctionBase
{
public:

	static CRunFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CRunFunction();
	~CRunFunction() = default;

	int _sign;
	CFile _codeFile;
	CProject::DataFileMapType _dataFiles;
};
