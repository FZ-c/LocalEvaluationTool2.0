#include "judgeFunc.h"

#include "Core/CommandManager/command.h"
#include "Core/Global/Output.h"

CJudgeFunction::CJudgeFunction()
{
	_functionName = "judge";
	_isAll = false;
	_hasCode = false;
	_hasData = false;
}

CJudgeFunction* CJudgeFunction::instance()
{
	static CJudgeFunction inst;
	return &inst;
}


bool CJudgeFunction::checkParams(std::vector<std::string> params)
{
	_hasCode = false;
	_hasData = false;
	_isAll = false;
	if (params.empty() || params.size() == 4 || params.size() > 5)
	{
		COutput::OutputErrorMessage("judge�����ʽ����\n");
		return false;
	}
	if(CCommand::instance()->getGppActiveSign() == false)
	{
		COutput::OutputErrorMessage("ϵͳδ��װG++���밲װ��ʹ��recheck����������ԣ�\n");
		return false;
	}
	_isAll = params.size() >= 2 && params[1] == "-a";
	if ((params.size() >= 2 && _isAll == false) || (params.size() >= 3 && _isAll == true))
	{
		int pos = 1 + (_isAll == true);
		params[pos] = CUtil::changePathAbsolute(params[pos]);
		CFile codeFile(params[pos]);
		if (codeFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[pos] + "�����ڣ�\n");
			return false;
		}
		if (codeFile.isCodeFile() == false)
		{
			COutput::OutputErrorMessage(codeFile.getAbsolutePath() + "���Ǵ����ļ���\n");
			return false;
		}
		_codeFile = codeFile;
		_hasCode = true;
	}
	if ((params.size() == 4 && _isAll == false) && (params.size() == 5 && _isAll == true))
	{
		int pos = 2 + (_isAll == true);
		params[pos] = CUtil::changePathAbsolute(params[pos]);
		CFile inputFile(params[pos]);
		if(inputFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[pos] + "�����ڣ�\n");
			return false;
		}
		if (inputFile.checkFileHasType(CUtil::calFileTypeValue(EFileTypeInputFile)) == false)
		{
			COutput::OutputErrorMessage(inputFile.getAbsolutePath() + "���������ļ���\n");
			return false;
		}
		params[pos + 1] = CUtil::changePathAbsolute(params[pos + 1]);
		CFile outputFile(params[pos + 1]);
		if (outputFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[pos + 1] + "�����ڣ�\n");
			return false;
		}
		if (outputFile.checkFileHasType(CUtil::calFileTypeValue(EFileTypeOutputFile)) == false)
		{
			COutput::OutputErrorMessage(outputFile.getAbsolutePath() + "��������ļ���\n");
			return false;
		}
		_dataFiles["tmp"] = std::make_pair(inputFile, outputFile);
		_hasData = true;
	}
	_params = params;
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
	if(_hasCode)
	{
		codeFiles.push_back(_codeFile);
	}
	else
	{
		codeFiles = project->getAllCodeFiles();
	}
	if(_hasData)
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
		allJudgeResult.push_back(judge->JudgeCode(*it, dataFiles, _isAll));
	}
	COutput::OutputSuccessMessage("\n\n�������!\n");
	for(SeqSJudgeResult::iterator it = allJudgeResult.begin();it != allJudgeResult.end();++it)
	{
		judge->printJudgeResult(*it);
	}
	return true;
}
