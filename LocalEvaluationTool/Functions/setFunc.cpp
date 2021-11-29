#include "setFunc.h"

#include "Core/CommandManager/command.h"
#include "Core/Global/Output.h"

CSetFunction::CSetFunction()
{
	_functionName = "set";
}

CSetFunction* CSetFunction::instance()
{
	static CSetFunction inst;
	return &inst;
}


bool CSetFunction::checkParams(std::vector<std::string> params)
{
	if (params.size() != 2)
	{
		COutput::OutputErrorMessage("set�����ʽ����\n");
		return false;
	}

	params[1] = CUtil::changePathAbsolute(params[1]);
	_params = params;
	return true;
}

bool CSetFunction::runFuction()
{
	if (getProject() == NULL)
	{
		COutput::OutputErrorMessage("���Projectȱʧ��\n");
		return false;
	}
	CProject newProject(_params[1]);
	if (newProject.isActive() == false)
	{
		COutput::OutputErrorMessage("set����ʧ�ܣ�(·������ʧ��)\n");
		return false;
	}
	*(getProject()) = newProject;
	COutput::OutputSuccessMessage("����·����" + newProject.getPath() + "\n");
	return true;
}
