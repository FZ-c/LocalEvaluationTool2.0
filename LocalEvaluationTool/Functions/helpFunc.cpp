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
		COutput::OutputErrorMessage("help�����ʽ����\n");
		return false;
	}
	return true;
}

bool CHelpFunction::runFuction()
{
	COutput::_OutputInf("This is a ûɶ���õ����⼧\n\n");
	COutput::_OutputInf("help ����˵��\n");
	COutput::_OutputInf("set [path] ����Ŀ¼\n");
	COutput::_OutputInf("recheck ���¼���Ҫ���\n");
	COutput::_OutputInf("run [codeFile] [dataFile] ����\n");
	COutput::_OutputInf("changeMode [-ACM/-OI]��������ģʽ\n");
	COutput::_OutputInf("judge [codeFile] [inputFile outputFile] ����\n");
	COutput::_OutputInf("flush [-all/-code/-data] ˢ�´���/�����ļ�\n");
	COutput::_OutputInf("show [-all/-code/-data] ��ʾɨ�赽���ļ�\n");
	return false;
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