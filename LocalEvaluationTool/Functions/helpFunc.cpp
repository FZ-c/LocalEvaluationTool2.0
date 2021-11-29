#include "helpFunc.h"

#include "core/Global/Output.h"

CHelpFunction::CHelpFunction()
{
	_functionName = "help";
}

CHelpFunction* CHelpFunction::instance()
{
	static CHelpFunction inst;
	return &inst;
}

bool CHelpFunction::checkParams(std::vector<std::string> params)
{
	if (params.size() > 1)
	{
		COutput::OutputErrorMessage("help命令格式错误！\n");
		return false;
	}
	return true;
}

bool CHelpFunction::runFuction()
{
	COutput::_OutputInf("This is a 没啥卵用的评测姬\n\n");
	COutput::_OutputInf("help 帮助说明\n");
	COutput::_OutputInf("set [path] 设置目录\n");
	COutput::_OutputInf("recheck 重新检查必要组件\n");
	COutput::_OutputInf("run [codeFile] [dataFile] 运行\n");
	COutput::_OutputInf("changeMode [-ACM/-OI]更改评测模式\n");
	COutput::_OutputInf("judge [codeFile] [inputFile outputFile] 测试\n");
	COutput::_OutputInf("flush [-all/-code/-data] 刷新代码/数据文件\n");
	COutput::_OutputInf("show [-all/-code/-data] 显示扫描到的文件\n");
	return false;
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