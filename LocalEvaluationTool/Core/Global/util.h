#pragma once

#include <string>
#include <ctime>
#include <direct.h>   
#include <sys/stat.h>
#include <io.h>
#include <vector>
#include <Windows.h>

#include "enum.h"

//调试开关
#define DEBUG_FUNCTION 0

class CUtil
{
public:
	static CUtil* instance();
	
	//移除字符串前后空格及中部多余空格
	static void removeBlank(std::string& str);
	
	//相对路径转绝对路径
	static std::string changePathAbsolute(std::string filePath);

	//后缀和文件类型互查
	int getFileType(std::string suffix);
	std::string getSuffix(int fileType);

	static bool addFloder(std::string path);

	//计算文件类型值（编译期计算）
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
	//开始计时
	void start();
	//停止计时
	void stop();
	//获取计时时长
	double getSpanTime();
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER startVal;
	LARGE_INTEGER stopVal;
};


// 获取绝对路径
// std::string get_absolute_path(std::string path)
// {
// 	char ret[256] = "";
// 	_fullpath(ret, path.c_str(), 256);
// 	return static_cast<std::string>(ret);
// }
// 
// 
// 将字符串中的rstr替换为nstr
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