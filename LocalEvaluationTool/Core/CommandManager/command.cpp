#include "command.h"

#include "helpFunc.h"
#include "showFunc.h"
#include "Core/Global/Output.h"
#include "Functions/changeModeFunc.h"
#include "Functions/flushFunc.h"
#include "Functions/judgeFunc.h"
#include "Functions/recheckFunc.h"
#include "Functions/runFunc.h"
#include "Functions/setFunc.h"

CCommand::CCommand() :_project("")
{
	COutput::_OutputInf("����ϵͳ...\n");
	//��ʼ������·����������
	TCHAR buff[1024];
	GetModuleFileName(nullptr, buff, 1024);
	char* chRtn = new char[512 * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, buff, -1, chRtn, 1024, nullptr, nullptr);
	std::string sRtn(chRtn);
	std::string suffix;
	CFile::splitFileStr(sRtn, _exePath, _exeName, suffix);
	_exeName += suffix;

	//����Ҫ����Ƿ����
	//G++
	checkGppIsActive();

	//��ʼ�����
	_project = CProject(_exePath);

	//���⴦�� exePathȥ�����һ��'\' ������ʾ
	if (_exePath.empty() == false && _exePath.back() == '\\') _exePath.pop_back();

	//�����ʾ��Ϣ
	COutput::_OutputInf("\n����\"help\"�鿴�����б�\n\n");

	//ע�᷽��
	registerFunc();
}

CCommand* CCommand::instance()
{
	static CCommand inst;
	return &inst;
}

void CCommand::getCmdParam()
{
	std::string cmd = _cmd + ' ';
	cmd.push_back(' ');
	_params.clear();
	std::string::size_type notSpacePos = cmd.find_first_not_of(" \t");
	while (notSpacePos != std::string::npos)
	{
		cmd.erase(0, notSpacePos);
		std::string::size_type spacePos = cmd.find_first_of(" \t");
		_params.push_back(cmd.substr(0, spacePos));
		cmd.erase(0, spacePos + 1);
		notSpacePos = cmd.find_first_not_of(" \t");
	}
}

void CCommand::runCommand(std::string command)
{
	_cmd = command;
	//�������
	getCmdParam();

	if(_params.empty())
	{
		return;
	}
	if(_funcMap.find(_params[0]) == _funcMap.end())
	{
		COutput::OutputErrorMessage("�޷����������" + _cmd + "\n");
		return;
	}
	//����ͷ���� �ȼ�����ö�Ӧ����
	if(_funcMap[_params[0]]->checkParams(_params))
	{
		_funcMap[_params[0]]->runFuction();
	}
}

//���G++�Ƿ��Ѱ�װ
bool CCommand::checkGppIsActive()
{
	_isGppActive = false;
	system("g++ --version >log.txt 2>&1");
	std::ifstream ifs("log.txt");
	std::string str;
	std::getline(ifs, str);
	ifs.close();
	if(str.find('\'') != std::string::npos)
	{
		COutput::OutputErrorMessage("G++ δ��װ�����޷��������⼰���в�����\n");
	}
	else
	{
		int pos = str.find_last_of(' ');
		std::string version = str.substr(pos + 1);
		COutput::OutputSuccessMessage("��ǰϵͳG++�汾��" + version + "\n");
		_isGppActive = true;
	}
	remove("log.txt");
	return _isGppActive;
}

bool CCommand::recheckGppIsActive()
{
	return checkGppIsActive();
}



//ע�Ṧ���� �����
void CCommand::registerFunc()
{
	//�����ܻ�����ע�����
	CFunctionBase::setProject(&_project);
	CFunctionBase::setJudgeManager(&_judge);

	_funcMap[CSetFunction::instance()->getFunctionName()] = CSetFunction::instance();
	_funcMap[CJudgeFunction::instance()->getFunctionName()] = CJudgeFunction::instance();
	_funcMap[CRunFunction::instance()->getFunctionName()] = CRunFunction::instance();
	_funcMap[CRecheckFunction::instance()->getFunctionName()] = CRecheckFunction::instance();
	_funcMap[CChangeModeFunction::instance()->getFunctionName()] = CChangeModeFunction::instance();
	_funcMap[CFlushFunction::instance()->getFunctionName()] = CFlushFunction::instance();
	_funcMap[CShowFunction::instance()->getFunctionName()] = CShowFunction::instance();
	_funcMap[CHelpFunction::instance()->getFunctionName()] = CHelpFunction::instance();
}

/*
 * set [path] ����Ŀ¼
 * judge [codeFile] [inputFile outputFile] ����
 * run [codeFile] [dataFile] ����
 * recheck ���¼���Ҫ���
 * changeMode [-ACM/-OI]��������ģʽ
 * flush [-all/-code/-data] ˢ�´���/�����ļ�
 * show [-all/-code/-data] ��ʾɨ�赽���ļ�
 * help
 */