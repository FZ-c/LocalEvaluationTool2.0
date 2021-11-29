#include "changeModeFunc.h"

#include "Core/Global/Output.h"

CChangeModeFunction::CChangeModeFunction()
{
	_functionName = "changeMode";
	_judgeType = EJudgeNone;
}

CChangeModeFunction* CChangeModeFunction::instance()
{
	static CChangeModeFunction inst;
	return &inst;
}

bool CChangeModeFunction::checkParams(std::vector<std::string> params)
{
	if(params.size() != 2)
	{
		COutput::OutputErrorMessage("changeMode命令格式错误！\n");
		return false;
	}
	if(params[1] == "-ACM")
	{
		_judgeType = EJudgeTypeACM;
	}
	else if(params[1] == "-OI")
	{
		_judgeType = EJudgeTypeOI;
	}
	else
	{
		COutput::OutputErrorMessage("评测模式" + params[1] + "不存在！请输入-ACM或者-OI！\n");
		return false;
	}
	return true;
}

bool CChangeModeFunction::runFuction()
{
	getJudgeManager()->setJudgeMode(_judgeType);
	return true;
}
