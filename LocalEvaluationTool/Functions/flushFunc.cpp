#include "flushFunc.h"

#include "core/Global/Output.h"

CFlushFunction::CFlushFunction()
{
	_functionName = "flush";
	_sign = 0;
}

CFlushFunction* CFlushFunction::instance()
{
	static CFlushFunction inst;
	return &inst;
}

bool CFlushFunction::checkParams(std::vector<std::string> params)
{
	if(params.size() > 2)
	{
		COutput::OutputErrorMessage("flush命令格式错误！\n");
		return false;
	}
	if (params[1] == "-all") 
	{
		_sign = 3;	//二进制11
	}
	else if(params[1] == "-code")
	{
		_sign = 1;	//二进制01
	}
	else if(params[1] == "-data")
	{
		_sign = 2;	//二进制10
	}
	else
	{
		COutput::OutputErrorMessage("参数错误，请输入-all/-code/-data的其中一个！\n");
		return false;
	}
	return true;
}

bool CFlushFunction::runFuction()
{
	if(_sign > 0 && _sign < 4)
	{
		getProject()->researchFiles(_sign & 1, _sign & 2);
		return true;
	}
	return false;
}
