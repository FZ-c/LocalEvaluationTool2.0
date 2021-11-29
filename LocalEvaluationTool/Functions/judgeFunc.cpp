#include "judgeFunc.h"

#include "Core/CommandManager/command.h"
#include "Core/Global/Output.h"

CJudgeFunction::CJudgeFunction()
{
	_functionName = "judge";
	_sign = 0;
}

CJudgeFunction* CJudgeFunction::instance()
{
	static CJudgeFunction inst;
	return &inst;
}


bool CJudgeFunction::checkParams(std::vector<std::string> params)
{
	if (params.empty() || params.size() == 3 || params.size() > 4)
	{
		COutput::OutputErrorMessage("judge�����ʽ����\n");
		return false;
	}
	if(CCommand::instance()->getGppActiveSign() == false)
	{
		COutput::OutputErrorMessage("ϵͳδ��װG++���밲װ��ʹ��recheck����������ԣ�\n");
		return false;
	}
	if (params.size() >= 2)
	{
		params[1] = CUtil::changePathAbsolute(params[1]);
		CFile codeFile(params[1]);
		if (codeFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[1] + "�����ڣ�\n");
			return false;
		}
		if (codeFile.isCodeFile() == false)
		{
			COutput::OutputErrorMessage(codeFile.getAbsolutePath() + "���Ǵ����ļ���\n");
			return false;
		}
		_codeFile = codeFile;
	}
	if (params.size() == 4)
	{
		params[2] = CUtil::changePathAbsolute(params[2]);
		CFile inputFile(params[2]);
		if(inputFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[2] + "�����ڣ�\n");
			return false;
		}
		if (inputFile.checkFileHasType(CUtil::calFileTypeValue(EFileTypeInputFile)) == false)
		{
			COutput::OutputErrorMessage(inputFile.getAbsolutePath() + "���������ļ���\n");
			return false;
		}
		params[2] = CUtil::changePathAbsolute(params[2]);
		CFile outputFile(params[2]);
		if (outputFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[2] + "�����ڣ�\n");
			return false;
		}
		if (outputFile.checkFileHasType(CUtil::calFileTypeValue(EFileTypeOutputFile)) == false)
		{
			COutput::OutputErrorMessage(outputFile.getAbsolutePath() + "��������ļ���\n");
			return false;
		}
		_dataFiles["tmp"] = std::make_pair(inputFile, outputFile);
	}
	_params = params;
	_sign = _params.size();
	return true;
}

bool CJudgeFunction::runFuction()
{
	CProject* project = getProject();
	CJudgeManager* judge = getJudgeManager();
	if (getProject() == NULL)
	{
		COutput::OutputErrorMessage("���Projectȱʧ��\n");
		return false;
	}
	if (getJudgeManager() == NULL)
	{
		COutput::OutputErrorMessage("���judgeManagerȱʧ��\n");
		return false;
	}
	//װ������
	SeqFile codeFiles;
	CProject::DataFileMapType dataFiles;
	if(_sign == 1)
	{
		codeFiles = project->getAllCodeFiles();
	}
	else
	{
		codeFiles.push_back(_codeFile);
	}
	if(_sign == 4)
	{
		dataFiles = _dataFiles;
	}
	else
	{
		dataFiles = project->getAllDataFiles();
	}
	//ִ������
	if(codeFiles.empty())
	{
		COutput::OutputErrorMessage("�����ڿ�����Ĵ����ļ���\n");
		return false;
	}
	if(dataFiles.empty())
	{
		COutput::OutputErrorMessage("�����������ļ������⣡\n");
		return false;
	}
	SeqSJudgeResult allJudgeResult;
	for (SeqFile::iterator it = codeFiles.begin(); it != codeFiles.end(); ++it)
	{
		allJudgeResult.push_back(judge->JudgeCode(*it, dataFiles));
	}
	COutput::OutputSuccessMessage("\n\n�������!\n");
	for(SeqSJudgeResult::iterator it = allJudgeResult.begin();it != allJudgeResult.end();++it)
	{
		judge->printJudgeResult(*it);
	}
	return true;
}
