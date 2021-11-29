#include "recheckFunc.h"

#include "Core/CommandManager/command.h"
#include "Core/Global/Output.h"

CRecheckFunction::CRecheckFunction()
{
	_functionName = "recheck";
}

CRecheckFunction* CRecheckFunction::instance()
{
	static CRecheckFunction inst;
	return &inst;
}

bool CRecheckFunction::checkParams(std::vector<std::string> params)
{
	if(params.size() != 1)
	{
		COutput::OutputErrorMessage("recheckÃüÁî¸ñÊ½´íÎó£¡\n");
		return false;
	}
	return true;
}

bool CRecheckFunction::runFuction()
{
	return CCommand::instance()->recheckGppIsActive();
}
