#pragma once

#include <map>

#include "file.h"

//指定CProject中的_dataFile按照文件名排序 如果是数字按照数字大小排序
struct DataFileMapSort
{
	//返回数字 如果存在非数字字符返回-1
	int getNum(const std::string& str) const
	{
		int ret = 0;
		int len = str.size();
		for (int i = 0; i < len; ++i)
		{
			if (str[i] < '0' || str[i] >'9') return -1;
			ret *= 10;
			ret += str[i] - '0';
		}
		return ret;
	}
	bool operator() (const std::string& str1, const std::string& str2) const
	{
		int num1 = getNum(str1);
		int num2 = getNum(str2);
		if (num1 != -1 && num2 != -1) return num1 < num2;
		if (num1 == -1 && num2 != -1) return false;
		if (num1 != -1 && num2 == -1) return true;
		return str1 < str2;
	}
};

class CProject
{
public:
	typedef std::map<std::string, CFilePair, DataFileMapSort> DataFileMapType;

	CProject(std::string path);
	~CProject() = default;

	//检查目录是否存在
	static bool checkDirExist(std::string dirName, bool printErr = true);

	//项目是否可用（可用：代码文件和数据文件均不为空）
	bool isActive() const { return _isActive; }

	//获取路径
	std::string getPath() const { return _path; }

	//获取数据文件
	const DataFileMapType& getAllDataFiles() const { return _dataFiles; }
	CFilePair getDataFilePair(std::string fileName);
	bool checkDataFileActive(std::string fileName);

	//获取代码文件
	const SeqFile& getAllCodeFiles() const { return _codeFiles; }
	CFile getCodeFile(const std::string& fileName);

	//重新扫描文件
	void researchFiles(bool codeFile = false, bool dataFile = false);

private:
	//获取路径下所有数据文件和代码文件
	bool _scanFiles(std::string path, bool searchCodeFile = true, bool searchDataFile = true);

private:

	std::string _path;
	bool _isActive;
	DataFileMapType _dataFiles;	//[FileName,(inputFile,outputFile)]
	SeqFile _codeFiles;
};
