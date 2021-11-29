#include "util.h"

#include "Output.h"

CUtil* CUtil::instance()
{
	static CUtil* inst = new CUtil();
	return inst;
}


CUtil::CUtil()
{
	//在这里进行一些全局变量的初始化

	//后缀对应文件类型map
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
	//去掉后面的空格
	while(str.empty() == false && str.back() == ' ')
	{
		str.pop_back();
	}
	//去掉前面的空格
	while(str[pos] == ' ' && pos < str.size())
	{
		pos++;
	}

	//遍历 存下非空格同时去掉中间多余空格
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
				COutput::_OutputInf("存在", COutput::enmCFC_Blue);
			else
				COutput::_OutputInf("不存在", COutput::enmCFC_Blue);
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
	//获取时钟频率
	QueryPerformanceFrequency(&frequency);
}

void CTimer::start()
{
	//获得计时器值
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
