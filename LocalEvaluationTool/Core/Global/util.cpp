#include "util.h"

#include "Output.h"

CUtil* CUtil::instance()
{
	static CUtil* inst = new CUtil();
	return inst;
}


CUtil::CUtil()
{
	//���������һЩȫ�ֱ����ĳ�ʼ��

	//��׺��Ӧ�ļ�����map
	_suffixMap.push_back(std::make_pair(".in", calFileTypeValue(EFileTypeInputFile)));
	_suffixMap.push_back(std::make_pair(".out", calFileTypeValue(EFileTypeOutputFile)));
	_suffixMap.push_back(std::make_pair(".encin", calFileTypeValue(EFileTypeInputFile, EFileEncryptTypeEncrypt)));
	_suffixMap.push_back(std::make_pair(".encout", calFileTypeValue(EFileTypeOutputFile, EFileEncryptTypeEncrypt)));
	_suffixMap.push_back(std::make_pair(".decin", calFileTypeValue(EFileTypeInputFile, EFileEncryptTypeDecrypt)));
	_suffixMap.push_back(std::make_pair(".decout", calFileTypeValue(EFileTypeOutputFile, EFileEncryptTypeDecrypt)));
	_suffixMap.push_back(std::make_pair(".c", calFileTypeValue(EFileTypeCCodeFile)));
	_suffixMap.push_back(std::make_pair(".cpp", calFileTypeValue(EFileTypeCPPCodeFile)));
}

void CUtil::removeBlank(std::string& str)
{
	size_t pos = 0;
	std::string ret;
	//ȥ������Ŀո�
	while(str.empty() == false && str.back() == ' ')
	{
		str.pop_back();
	}
	//ȥ��ǰ��Ŀո�
	while(str[pos] == ' ' && pos < str.size())
	{
		pos++;
	}

	//���� ���·ǿո�ͬʱȥ���м����ո�
	for (; pos < str.size();)
	{
		if(str[pos] == ' ')
		{
			ret.push_back(' ');
			while(str[pos++] != ' ' || pos == str.size() - 1)
			{
				break;
			}
		}
		else
		{
			ret.push_back(str[pos++]);
		}
	}
	str = ret;
}

std::string CUtil::changePathAbsolute(std::string filePath)
{
	char ret[512] = "";
	_fullpath(ret, filePath.c_str(), 512);
	return ret;
}

int CUtil::getFileType(std::string suffix)
{
	std::vector<std::pair<std::string, int>>::iterator it =
	std::find_if(_suffixMap.begin(), _suffixMap.end(), [suffix](std::pair<std::string, int> p)
	{
		return p.first == suffix;
	});
	if(it != _suffixMap.end())
	{
		return it->second;
	}
	return calFileTypeValue(EFileTypeError);
}

std::string CUtil::getSuffix(int fileType)
{
	std::vector<std::pair<std::string, int>>::iterator it =
		std::find_if(_suffixMap.begin(), _suffixMap.end(), [fileType](std::pair<std::string, int> p)
			{
				return p.second == fileType;
			});
	if (it != _suffixMap.end())
	{
		return it->first;
	}
	return "";
}

bool CUtil::addFloder(std::string path)
{
#if DEBUGMODE
	COutput::_OutputInf(path + "\n", COutput::enmCFC_Blue);
#endif
	size_t dirPathLen = path.length();
	std::string tmpDirPath;
	for (size_t i = 0; i < dirPathLen; ++i)
	{
		tmpDirPath += path[i];
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
#if DEBUGMODE
			COutput::_OutputInf(tmpDirPath, COutput::enmCFC_Blue);
			std::cout << tmpDirPath;
			if (_access(tmpDirPath.c_str(), 0))
				COutput::_OutputInf("����", COutput::enmCFC_Blue);
			else
				COutput::_OutputInf("������", COutput::enmCFC_Blue);
#endif
			if (_access(tmpDirPath.c_str(), 0))
			{
				int ret = _mkdir(tmpDirPath.c_str());
				if (ret) return false;
			}
		}
	}
	return true;
}


/************************************
 *              CTimer
 ************************************/
CTimer::CTimer()
{
	//��ȡʱ��Ƶ��
	QueryPerformanceFrequency(&frequency);
}

void CTimer::start()
{
	//��ü�ʱ��ֵ
	QueryPerformanceCounter(&startVal);
}

void CTimer::stop()
{
	QueryPerformanceCounter(&stopVal);
}

double CTimer::getSpanTime()
{
	long long interval = stopVal.QuadPart - startVal.QuadPart;
	return interval / (double)frequency.QuadPart;
}
