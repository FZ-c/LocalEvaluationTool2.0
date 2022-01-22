#pragma once

#include "Core/FileManager/file.h"
#include "Core/FileManager/project.h"
#include "Core/JudgeManager/judge.h"
#include "Functions/Base/functionBaseManager.h"

class CCommand
{
public:

	static CCommand* instance();

	const std::string& getExePath() const { return _exePath; }

	void runCommand(const std::string& command);

	bool getGppActiveSign() { return _isGppActive; }

	bool recheckGppIsActive();

private:
	CCommand();
	~CCommand() = default;

	void getCmdParam();

	void registerFunc();

	bool checkGppIsActive();

	std::string _exePath;
	std::string _exeName;
	std::string _cmd;
	std::vector<std::string> _params;
	std::map<std::string, CFunctionBase*> _funcMap;

	bool _isGppActive;

	CProject _project;
	CJudgeManager _judge;
};

/*
 * set [ProjectPath] ����·��
 * judge [codeFile] [inputFile outputFile] ����
 * run [codeFile] [dataFile] ����
 * flush [-all] [-code] [-data] ˢ�´���/�����ļ�
 * show [-all] [-code] [-data] ��ʾɨ�赽���ļ�
 * help
 */