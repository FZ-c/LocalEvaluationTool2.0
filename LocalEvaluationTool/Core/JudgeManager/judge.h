#pragma once
#include "Core/FileManager/project.h"

struct SPointResult
{
	std::string inputFileName;	//输入文件名
	bool successRun;		//是否成功运行
	double runTime;			//运行时间
	long long memoryUse;	//使用的内存峰值
	bool outputFileCheck;	//输出文件检验一致
	SPointResult()
	{
		inputFileName = "";
		successRun = false;
		runTime = 0;
		memoryUse = 0;
		outputFileCheck = false;
	}
};
typedef std::vector<SPointResult> SeqSPointResult;

struct SJudgeResult
{
	std::string codeFileName;	//判题代码名
	bool successCompile;	//是否成功编译
	bool successRun;		//是否成功运行
	double runTime;			//运行时间
	long long memoryUse;	//使用的内存峰值
	bool outputFileCheck;	//输出文件检验一致
	int pointNum;			//数据点个数
	SeqSPointResult pointsResult;	//数据点信息
	SJudgeResult()
	{
		successCompile = false;
		successRun = false;
		runTime = 0;
		memoryUse = 0;
		outputFileCheck = false;
		pointNum = 0;
	}
};
typedef std::vector<SJudgeResult> SeqSJudgeResult;

class CJudgeManager
{
public:
	CJudgeManager();
	~CJudgeManager() = default;

	//判题
	SJudgeResult JudgeCode(const CFile& codeFiles, const CProject::DataFileMapType& dataFiles, bool isAll);

	//运行代码
	SJudgeResult runCode(const CFile& codeFile, const CFile& inputFile, std::string outputFile, bool needCompile = true, bool delExe = false, bool printErrorMessage = false);
	
	//编译
	bool compileCodeFile(const CFile& codeFile, bool printErrorMessage = false);

	void printJudgeResult(SJudgeResult& result);

	void setJudgeMode(EJudgeType judgeType);

private:
	//编译代码 成功返回true
	bool compile(const CFile& codeFile);

	//比较两个文件的异同
	bool compareFile(const std::string& fileName1, const std::string& fileName2);

	void printPointResult(SPointResult& result, int pointNumber);

	void printProgressBar(SJudgeResult& result, bool hasNext = false);

private:
	EJudgeType _judgeMode;
};