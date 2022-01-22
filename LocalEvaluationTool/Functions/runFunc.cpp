#include "runFunc.h"

#include "Core/CommandManager/command.h"
#include "Core/Global/Output.h"

CRunFunction::CRunFunction()
{
	_functionName = "run";
	_sign = 0;
}

CRunFunction* CRunFunction::instance()
{
	static CRunFunction inst;
	return &inst;
}

bool CRunFunction::checkParams(std::vector<std::string> params)
{
	if (params.empty() || params.size() == 3 || params.size() > 4)
	{
		COutput::OutputErrorMessage("run命令格式错误！\n");
		return false;
	}
	if (CCommand::instance()->getGppActiveSign() == false)
	{
		COutput::OutputErrorMessage("系统未安装G++！请安装后使用recheck命令检查后重试！\n");
		return false;
	}
	if (params.size() >= 2)
	{
		params[1] = CUtil::changePathAbsolute(params[1]);
		CFile codeFile(params[1]);
		if (codeFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[1] + "不存在！\n");
			return false;
		}
		if (codeFile.isCodeFile() == false)
		{
			COutput::OutputErrorMessage(codeFile.getAbsolutePath() + "不是代码文件！\n");
			return false;
		}
		_codeFile = codeFile;
	}
	if (params.size() == 4)
	{
		params[2] = CUtil::changePathAbsolute(params[2]);
		CFile inputFile(params[2]);
		if (inputFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[2] + "不存在！\n");
			return false;
		}
		if (inputFile.checkFileHasType(CUtil::calFileTypeValue(EFileTypeInputFile)) == false)
		{
			COutput::OutputErrorMessage(inputFile.getAbsolutePath() + "不是输入文件！\n");
			return false;
		}
		params[2] = CUtil::changePathAbsolute(params[2]);
		CFile outputFile(params[2]);
		if (outputFile.checkFileWork() == false)
		{
			COutput::OutputErrorMessage(params[2] + "不存在！\n");
			return false;
		}
		if (outputFile.checkFileHasType(CUtil::calFileTypeValue(EFileTypeOutputFile)) == false)
		{
			COutput::OutputErrorMessage(outputFile.getAbsolutePath() + "不是输出文件！\n");
			return false;
		}
		_dataFiles["tmp"] = std::make_pair(inputFile, outputFile);
	}
	_params = params;
	_sign = _params.size();
	return true;
}

bool CRunFunction::runFuction()
{
	CProject* project = getProject();
	CJudgeManager* judge = getJudgeManager();
	if (getProject() == NULL)
	{
		COutput::OutputErrorMessage("组件Project缺失！\n");
		return false;
	}
	if (getJudgeManager() == NULL)
	{
		COutput::OutputErrorMessage("组件judgeManager缺失！\n");
		return false;
	}
	//装填数据
	SeqFile codeFiles;
	CProject::DataFileMapType dataFiles;
	if (_sign == 1)
	{
		codeFiles = project->getAllCodeFiles();
	}
	else
	{
		codeFiles.push_back(_codeFile);
	}
	if (_sign == 4)
	{
		dataFiles = _dataFiles;
	}
	else
	{
		dataFiles = project->getAllDataFiles();
	}
	if (codeFiles.empty())
	{
		COutput::OutputErrorMessage("不存在可运行的代码文件！\n");
		return false;
	}
	if (dataFiles.empty())
	{
		COutput::OutputErrorMessage("不存在数据文件供运行！\n");
		return false;
	}
	//执行运行
	for (SeqFile::iterator codeIt = codeFiles.begin(); codeIt != codeFiles.end(); ++codeIt)
	{
		//先编译，编译过了再运行
		if(judge->compileCodeFile(*codeIt,true) == true)
		{
			//创建对应的文件夹
			std::string retPath = getProject()->getPath() + codeIt->getFileName() + "\\";
			CUtil::addFloder(retPath);
			int pointNum = 1;
			for (CProject::DataFileMapType::iterator dataIt = dataFiles.begin(); dataIt != dataFiles.end(); ++dataIt)
			{
				COutput::OutputFleshMessage("正在运行文件:" + dataIt->second.first.getAbsolutePath() + 
					" (" + std::to_string(pointNum) + "/" + std::to_string(dataFiles.size()) + ")", 
					COutput::enmCFC_Cyan);
				std::string outFilePath = retPath + dataIt->second.first.getFileName() + ".out";
				judge->runCode(*codeIt, dataIt->second.first, outFilePath, false, pointNum++ == dataFiles.size(), true);
			}
			COutput::OutputFleshMessage(codeIt->getAbsolutePath() + " 执行完毕！输出文件位置：" + retPath + "\n",COutput::enmCFC_Green);
		}
	}
	return true;
}
