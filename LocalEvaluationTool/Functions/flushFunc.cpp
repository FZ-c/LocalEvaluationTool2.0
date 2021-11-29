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
		COutput::OutputErrorMessage("flush�����ʽ����\n");
		return false;
	}
	if (params[1] == "-all") 
	{
		_sign = 3;	//������11
	}
	else if(params[1] == "-code")
	{
		_sign = 1;	//������01
	}
	else if(params[1] == "-data")
	{
		_sign = 2;	//������10
	}
	else
	{
		COutput::OutputErrorMessage("��������������-all/-code/-data������һ����\n");
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
