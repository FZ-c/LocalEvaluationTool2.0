#pragma once

#include <string>
#include <ctime>
#include <direct.h>   
#include <sys/stat.h>
#include <io.h>
#include <vector>
#include <Windows.h>

#include "enum.h"

//���Կ���
#define DEBUG_FUNCTION 0

class CUtil
{
public:
	static CUtil* instance();
	
	//�Ƴ��ַ���ǰ��ո��в�����ո�
	static void removeBlank(std::string& str);
	
	//���·��ת����·��
	static std::string changePathAbsolute(std::string filePath);

	//��׺���ļ����ͻ���
	int getFileType(std::string suffix);
	std::string getSuffix(int fileType);

	static bool addFloder(std::string path);

	//�����ļ�����ֵ�������ڼ��㣩
	static constexpr int calFileTypeValue(EFileType fileType, EFileEncryptType encryptType = EFileEncryptTypeNormal)
	{
		return fileType + (encryptType << FILE_TYPE_MAX_LEN);
	}
	
	std::vector<std::pair<std::string, int>> _suffixMap;
private:
	CUtil();
	~CUtil() = default;
};

class CTimer
{
public:
	CTimer();
	//��ʼ��ʱ
	void start();
	//ֹͣ��ʱ
	void stop();
	//��ȡ��ʱʱ��
	double getSpanTime();
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER startVal;
	LARGE_INTEGER stopVal;
};


// ��ȡ����·��
// std::string get_absolute_path(std::string path)
// {
// 	char ret[256] = "";
// 	_fullpath(ret, path.c_str(), 256);
// 	return static_cast<std::string>(ret);
// }
// 
// 
// ���ַ����е�rstr�滻Ϊnstr
// std::string replace_string(std::string str, std::string rstr, std::string nstr)
// {
// 	std::string ans;
// 	for (int i = 0; i < str.size(); i++)
// 	{
// 		bool succeed = false;
// 		if (str[i] == rstr[0])
// 		{
// 			succeed = true;
// 			for (int j = 1; j < rstr.size(); j++)
// 			{
// 				if (str[i + j] != rstr[j])
// 				{
// 					succeed = false;
// 					break;
// 				}
// 			}
// 		}
// 		if (succeed)
// 		{
// 			ans += nstr;
// 			i += rstr.size() - 1;
// 		}
// 		else
// 			ans += str[i];
// 	}
// 	return ans;
// }