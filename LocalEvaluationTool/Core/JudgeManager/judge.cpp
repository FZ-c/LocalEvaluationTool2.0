#include "judge.h"
#include "Core/Global/util.h"
#include "Core/Global/Output.h"

#include <fstream>


CJudgeManager::CJudgeManager()
{
	_judgeMode = EJudgeTypeACM;
}


//编译成功返回true 否则返回false
//如果编译失败，会存在文件log.txt在代码文件目录中
bool CJudgeManager::compile(const CFile& codeFile)
{
	if(codeFile.checkFileWork() == false || codeFile.isCodeFile() == false)
	{
		return false;
	}

	//输出log文件路径
	std::string logFilePath = codeFile.getPath() + "log.txt";

#if DEBUGMODE
	COutput::_OutputInf("g++ -o " + nameTmp + " " + codeName + " >" + logFilePath + " 2>&1\n", COutput::enmCFC_Cyan);
#endif

	system(("g++ -o " + codeFile.getFileName() + " " + codeFile.getAbsolutePath() + " >" + logFilePath + " 2>&1").c_str());
	
	bool is_error = (CFile::getFileSize(logFilePath) > 0);
	return !is_error;
}

//比较两个文件的异同
bool CJudgeManager::compareFile(std::string fileName1, std::string fileName2)
{
	system(static_cast<std::string>("fc " + fileName1 + " " + fileName2 + " 1> ret.ret").c_str());
	std::ifstream ifs("ret.ret");
	bool ret = false;
	if (ifs.is_open())
	{
		std::string input;
		std::getline(ifs, input);
		if (input.find("正在比较文件") == std::string::npos)
		{
			ret = false;
		}
		else
		{
			std::getline(ifs, input);
			if (input == "FC: 找不到差异")
			{
				ret = true;
			}
		}
	}
	ifs.close();
	remove("ret.ret");
	return ret;
}

bool CJudgeManager::compileCodeFile(const CFile& codeFile, bool printErrorMessage/* = false*/)
{
	//输出log文件路径
	std::string logFilePath = codeFile.getPath() + "log.txt";

	if (!compile(codeFile))
	{
		bool isError = (CFile::getFileSize(logFilePath) > 0);
		if(isError)
		{
			COutput::OutputErrorMessage("文件: " + codeFile.getAbsolutePath() + "编译失败！\n\n");
			if(printErrorMessage)
			{
				std::ifstream ifs(logFilePath);
				std::string out;
				while(ifs.good())
				{
					getline(ifs, out);
					if (!out.empty())
					{
						COutput::_OutputInf(out + "\n", COutput::enmCFC_Red);
					}
				}
				ifs.close();
			}
			if (remove(logFilePath.c_str()) && printErrorMessage)
			{
				COutput::OutputWarningMessage("log文件删除失败！(ErrCode:-12)\n");
			}
		}
		return false;
	}
	else
	{
		COutput::OutputSuccessMessage("文件: " + codeFile.getAbsolutePath() + " 编译成功!\n\n");
		if (remove(logFilePath.c_str()) && printErrorMessage)
		{
			COutput::OutputWarningMessage("log文件删除失败！(ErrCode:-13)\n");
		}
		return true;
	}
}

SJudgeResult CJudgeManager::runCode(const CFile& codeFile, const CFile& inputFile, std::string outputFile, bool needCompile/* = true*/, bool delExe/* = false*/, bool printErrorMessage/* = false*/)
{
	SJudgeResult ret;
	if (needCompile == false)
	{
		ret.successCompile = true;
	}
	else
	{
		ret.successCompile = compileCodeFile(codeFile, true);
	}
	if (ret.successCompile)
	{
		std::string logFilePath = codeFile.getPath() + "log1.txt";

		CTimer timer;
		timer.start();
		system((codeFile.getFileName() + ".exe <" + inputFile.getAbsolutePath() + " 1>" + outputFile + "" + " 2>" + logFilePath).c_str());
		timer.stop();
		ret.runTime = timer.getSpanTime();

		ret.successRun = (CFile::getFileSize(logFilePath) <= 0);
		if(ret.successRun == false && printErrorMessage)
		{
			COutput::_OutputInf("\n");
			std::ifstream ifs(logFilePath);
			std::string out;
			while (ifs.good())
			{
				getline(ifs, out);
				if (!out.empty())
				{
					COutput::_OutputInf(out, COutput::enmCFC_Red);
				}
			}
			ifs.close();
		}
		remove(logFilePath.c_str());
		if(delExe)
		{
			remove((codeFile.getFileName() + ".exe").c_str());
		}
	}
	return ret;
}

SJudgeResult CJudgeManager::JudgeCode(const CFile& codeFile, const CProject::DataFileMapType& dataFiles)
{
	SJudgeResult ret;
	if(_judgeMode == EJudgeNone)
	{
		COutput::OutputErrorMessage("评测模式未设置，请使用changeMode命令设置评测模式！\n\n");
		return ret;
	}
	if(!codeFile.checkFileWork())
	{
		COutput::OutputErrorMessage("代码文件不可用！\n\n");
		return ret;
	}
	if(dataFiles.empty())
	{
		COutput::OutputErrorMessage("不存在测试文件！\n\n");
		return ret;
	}
	ret.codeFileName = codeFile.getFileCompleteName();
	ret.pointNum = dataFiles.size();
	ret.successCompile = compileCodeFile(codeFile.getAbsolutePath(), true);
	if(ret.successCompile)
	{
		int pointNumber = 1;
		for (CProject::DataFileMapType::const_iterator dataFileIt = dataFiles.begin(); dataFileIt != dataFiles.end(); ++dataFileIt)
		{
			COutput::OutputFleshMessage("正在判题: #" + std::to_string(pointNumber) + ":(" + dataFileIt->second.first.getAbsolutePath() + ")", COutput::enmCFC_Purple);
			SJudgeResult tmpResult = runCode(codeFile, dataFileIt->second.first, codeFile.getPath() + "a.txt", false, false, false);
			SPointResult pointResult;
			pointResult.inputFileName = dataFileIt->second.first.getAbsolutePath();
			pointResult.successRun = tmpResult.successRun;
			pointResult.runTime = tmpResult.runTime;
			pointResult.outputFileCheck = compareFile(dataFileIt->second.second.getAbsolutePath(), codeFile.getPath() + "a.txt");
			ret.pointsResult.push_back(pointResult);
			remove((codeFile.getPath() + "a.txt").c_str());
			printPointResult(pointResult, pointNumber++);

			if(_judgeMode == EJudgeTypeACM && (pointResult.successRun == false || pointResult.outputFileCheck == false))
			{
				break;
			}
		}
		remove((codeFile.getFileName() + ".exe").c_str());
	}
	printJudgeResult(ret);
	return ret;
}

void CJudgeManager::printPointResult(SPointResult& result, int pointNumber)
{
	std::string out = "#" + std::to_string(pointNumber) + ":";
	COutput::ConsoleForegroundColor outColor = COutput::enmCFC_Red;
	if(result.successRun == false)
	{
		out += "RunTime Error ";
	}
	else if(result.outputFileCheck == false)
	{
		out += "Wrong Answer ";
	}
	else
	{
		out += "Accepted ";
		out += "[";
		std::string timeStr = std::to_string(((long long)(result.runTime * 100000) / 100.0));
		out += timeStr.substr(0, timeStr.find('.') + 3);
		out += " ms]  ";
		outColor = COutput::enmCFC_Green;
	}
	out += '(';
	out += result.inputFileName;
	out += ")\n";
	COutput::OutputFleshMessage(out, outColor);
}

void CJudgeManager::printJudgeResult(SJudgeResult& result)
{
	std::string out = result.codeFileName + ": ";
	COutput::ConsoleForegroundColor outColor = COutput::enmCFC_Red;

	if (_judgeMode == EJudgeTypeACM)
	{
		bool isPass = result.successCompile;
		if(!isPass)
		{
			out += "Compile Error";
		}
		else
		{
			for (SeqSPointResult::iterator it = result.pointsResult.begin(); it != result.pointsResult.end(); ++it)
			{
				if (it->successRun == true && it->outputFileCheck == true)
				{
					//时间取最大
					if (result.runTime == 0.0 || result.runTime < it->runTime)
					{
						result.runTime = it->runTime;
					}
				}
				else
				{
					//最多只会有一个错误的且一定在最后
					if (it->successRun == false)
					{
						out += "RunTime Error in #" + std::to_string(result.pointsResult.size());
					}
					else if (it->outputFileCheck == false)
					{
						out += "Wrong Answer in #" + std::to_string(result.pointsResult.size());
					}
					isPass = false;
				}
			}
			if (isPass)
			{
				out += "Accepted ";
				out += "[";
				std::string timeStr = std::to_string(((long long)(result.runTime * 100000) / 100.0));
				out += timeStr.substr(0, timeStr.find('.') + 3);
				out += " ms]  ";
				outColor = COutput::enmCFC_Green;
			}
		}
		out += "  Total:" + std::to_string(result.pointNum) + " point(s)";
	}
	else
	{
		std::string errorName;
		int passPointNum = 0;
		if(result.successCompile == false)
		{
			errorName = "Compile Error";
		}
		else
		{
			for (SeqSPointResult::iterator it = result.pointsResult.begin(); it != result.pointsResult.end(); ++it)
			{
				//时间累加
				if (it->successRun == true && it->outputFileCheck == true)
				{
					result.runTime += it->runTime;
					passPointNum++;
				}
				else
				{
					if (it->successRun == false)
					{
						if (errorName.empty() == false && errorName != "RunTime Error ")
						{
							errorName = "Multiple Errors ";
						}
						else
						{
							errorName = "RunTime Error ";
						}
					}
					else if (it->outputFileCheck == false)
					{
						if (errorName.empty() == false && errorName != "Wrong Answer ")
						{
							errorName = "Multiple Errors ";
						}
						else
						{
							errorName = "Wrong Answer ";
						}
					}
				}
			}
		}
		if (passPointNum == result.pointNum)
		{
			out += "Accepted ";
		}
		else
		{
			out += errorName;
		}
		out += std::to_string(passPointNum) + "/" + std::to_string(result.pointNum);
		if(passPointNum == result.pointNum)
		{
			out += "[";
			std::string timeStr = std::to_string(((long long)(result.runTime * 100000) / 100.0));
			out += timeStr.substr(0, timeStr.find('.') + 3);
			out += " ms]";
			outColor = COutput::enmCFC_Green;
		}
	}
	COutput::_OutputInf(out + "\n", outColor);
}

void CJudgeManager::setJudgeMode(EJudgeType judgeType)
{
	_judgeMode = judgeType;
}
