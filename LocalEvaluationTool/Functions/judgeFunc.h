#pragma once
#include <string>
#include <vector>

#include "Base/functionBaseManager.h"

class CJudgeFunction : public CFunctionBase
{
public:

	static CJudgeFunction* instance();

	bool checkParams(std::vector<std::string> params);

	bool runFuction();
private:
	CJudgeFunction();
	~CJudgeFunction() = default;

	bool _isAll;
	bool _hasCode;
	bool _hasData;
	CFile _codeFile;
	CProject::DataFileMapType _dataFiles;
};
