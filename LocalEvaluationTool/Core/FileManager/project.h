#pragma once

#include <map>

#include "file.h"

//ָ��CProject�е�_dataFile�����ļ������� ��������ְ������ִ�С����
struct DataFileMapSort
{
	//�������� ������ڷ������ַ�����-1
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

	//���Ŀ¼�Ƿ����
	static bool checkDirExist(std::string dirName, bool printErr = true);

	//��Ŀ�Ƿ���ã����ã������ļ��������ļ�����Ϊ�գ�
	bool isActive() const { return _isActive; }

	//��ȡ·��
	std::string getPath() const { return _path; }

	//��ȡ�����ļ�
	const DataFileMapType& getAllDataFiles() const { return _dataFiles; }
	CFilePair getDataFilePair(std::string fileName);
	bool checkDataFileActive(std::string fileName);

	//��ȡ�����ļ�
	const SeqFile& getAllCodeFiles() const { return _codeFiles; }
	CFile getCodeFile(const std::string& fileName);

	//����ɨ���ļ�
	void researchFiles(bool codeFile = false, bool dataFile = false);

private:
	//��ȡ·�������������ļ��ʹ����ļ�
	bool _scanFiles(std::string path, bool searchCodeFile = true, bool searchDataFile = true);

private:

	std::string _path;
	bool _isActive;
	DataFileMapType _dataFiles;	//[FileName,(inputFile,outputFile)]
	SeqFile _codeFiles;
};
