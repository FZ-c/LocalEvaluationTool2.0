#pragma once
#include "Core/FileManager/project.h"

struct SPointResult
{
	std::string inputFileName;	//�����ļ���
	bool successRun;		//�Ƿ�ɹ�����
	double runTime;			//����ʱ��
	long long memoryUse;	//ʹ�õ��ڴ��ֵ
	bool outputFileCheck;	//����ļ�����һ��
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
	std::string codeFileName;	//���������
	bool successCompile;	//�Ƿ�ɹ�����
	bool successRun;		//�Ƿ�ɹ�����
	double runTime;			//����ʱ��
	long long memoryUse;	//ʹ�õ��ڴ��ֵ
	bool outputFileCheck;	//����ļ�����һ��
	int pointNum;			//���ݵ����
	SeqSPointResult pointsResult;	//���ݵ���Ϣ
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

	//����
	SJudgeResult JudgeCode(const CFile& codeFiles, const CProject::DataFileMapType& dataFiles, bool isAll);

	//���д���
	SJudgeResult runCode(const CFile& codeFile, const CFile& inputFile, std::string outputFile, bool needCompile = true, bool delExe = false, bool printErrorMessage = false);
	
	//����
	bool compileCodeFile(const CFile& codeFile, bool printErrorMessage = false);

	void printJudgeResult(SJudgeResult& result);

	void setJudgeMode(EJudgeType judgeType);

private:
	//������� �ɹ�����true
	bool compile(const CFile& codeFile);

	//�Ƚ������ļ�����ͬ
	bool compareFile(const std::string& fileName1, const std::string& fileName2);

	void printPointResult(SPointResult& result, int pointNumber);

	void printProgressBar(SJudgeResult& result, bool hasNext = false);

private:
	EJudgeType _judgeMode;
};