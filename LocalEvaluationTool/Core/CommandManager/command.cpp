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
	COutput::_OutputInf("启动系统...\n");
	//初始化程序路径及程序名
	TCHAR buff[1024];
	GetModuleFileName(nullptr, buff, 1024);
	char* chRtn = new char[512 * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, buff, -1, chRtn, 1024, nullptr, nullptr);
	std::string sRtn(chRtn);
	std::string suffix;
	CFile::splitFileStr(sRtn, _exePath, _exeName, suffix);
	_exeName += suffix;

	//检查必要组件是否存在
	//G++
	checkGppIsActive();

	//初始化组件
	_project = CProject(_exePath);

	//特殊处理 exePath去掉最后一个'\' 用于显示
	if (_exePath.empty() == false && _exePath.back() == '\\') _exePath.pop_back();

	//输出提示信息
	COutput::_OutputInf("\n输入\"help\"查看命令列表\n\n");

	//注册方法
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
	//拆解命令
	getCmdParam();

	if(_params.empty())
	{
		return;
	}
	if(_funcMap.find(_params[0]) == _funcMap.end())
	{
		COutput::OutputErrorMessage("无法解析的命令：" + _cmd + "\n");
		return;
	}
	//命令头存在 先检查后调用对应方法
	if(_funcMap[_params[0]]->checkParams(_params))
	{
		_funcMap[_params[0]]->runFuction();
	}
}

//检查G++是否已安装
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
		COutput::OutputErrorMessage("G++ 未安装！将无法进行评测及运行操作！\n");
	}
	else
	{
		int pos = str.find_last_of(' ');
		std::string version = str.substr(pos + 1);
		COutput::OutputSuccessMessage("当前系统G++版本：" + version + "\n");
		_isGppActive = true;
	}
	remove("log.txt");
	return _isGppActive;
}

bool CCommand::recheckGppIsActive()
{
	return checkGppIsActive();
}



//注册功能类 放最后
void CCommand::registerFunc()
{
	//往功能基类中注册组件
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
 * set [path] 设置目录
 * judge [codeFile] [inputFile outputFile] 测试
 * run [codeFile] [dataFile] 运行
 * recheck 重新检查必要组件
 * changeMode [-ACM/-OI]更改评测模式
 * flush [-all/-code/-data] 刷新代码/数据文件
 * show [-all/-code/-data] 显示扫描到的文件
 * help
 */