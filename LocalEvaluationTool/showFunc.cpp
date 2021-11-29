#include "showFunc.h"

#include "Core/Global/Output.h"

CShowFunction::CShowFunction()
{
	_functionName = "show";
	_sign = 0;
}

CShowFunction* CShowFunction::instance()
{
	static CShowFunction inst;
	return &inst;
}

bool CShowFunction::checkParams(std::vector<std::string> params)
{
	if (params.size() > 2)
	{
		COutput::OutputErrorMessage("show�����ʽ����\n");
		return false;
	}
	if (params[1] == "-all")
	{
		_sign = 3;	//������11
	}
	else if (params[1] == "-code")
	{
		_sign = 1;	//������01
	}
	else if (params[1] == "-data")
	{
		_sign = 2;	//������10
	}
	else
	{
		COutput::OutputErrorMessage("��������������-all/-code/-data������һ����\n");
		return false;
	}
	return true;
}

bool CShowFunction::runFuction()
{
	if (_sign > 0 && _sign < 4)
	{
		if(_sign & 1)
		{
			const SeqFile& codeFiles = getProject()->getAllCodeFiles();
			if(codeFiles.empty())
			{
				COutput::OutputErrorMessage("�޴����ļ���\n");
			}
			else
			{
				COutput::_OutputInf("�����ļ���\n", COutput::enmCFC_Yellow);
				for (SeqFile::const_iterator it = codeFiles.begin(); it != codeFiles.end(); ++it)
				{
					COutput::_OutputInf(it->getAbsolutePath() + "\n", COutput::enmCFC_Yellow);
				}
			}
		}
		if (_sign & 2)
		{
			const CProject::DataFileMapType& dataFiles = getProject()->getAllDataFiles();
			if (dataFiles.empty())
			{
				COutput::OutputErrorMessage("�޴����ļ���\n");
			}
			else
			{
				COutput::_OutputInf("�����ļ���\n", COutput::enmCFC_Purple);
				for (CProject::DataFileMapType::const_iterator it = dataFiles.begin(); it != dataFiles.end(); ++it)
				{
					COutput::_OutputInf(it->second.first.getAbsolutePath() + "\n", COutput::enmCFC_Purple);
					COutput::_OutputInf(it->second.second.getAbsolutePath() + "\n", COutput::enmCFC_Purple);
				}
			}
		}
		return true;
	}
	return false;
}
