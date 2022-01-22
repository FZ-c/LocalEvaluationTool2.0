#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "Core/Global/util.h"

/*
 * �ļ�������
 */
class CFile
{
public:
	CFile(const std::string& fileName);
	CFile();
	~CFile() = default;

	//����ļ��Ƿ����
	static bool checkFileExist(std::string fileName, bool printErr = false);
	
	const std::string& getFileName() const { return _name; }
	std::string getFileCompleteName() const { return _name + _suffix; }
	const std::string& getAbsolutePath() const { return _absolutePath; }
	const std::string& getPath() const { return _path; }
	const int& getFileType() const { return _type; }

	//����ļ��Ƿ���ĳ����
	bool checkFileHasType(int checkType) const;

	//����ļ��Ƿ�����
	bool checkFileWork() const { return checkFileHasType(CUtil::calFileTypeValue(EFileTypeError)) == false; }

	//����ļ��Ƿ�Ϊ�����ļ�
	bool isCodeFile() const;

	//����ļ��Ƿ�Ϊ�����ļ�
	bool isDataFile() const;

	//�ָ��ļ�������
	static void splitFileStr(std::string fileStr, std::string& filePath, std::string& fileName, std::string& fileSuffix);

	//��ȡ�ļ���С
	static int getFileSize(std::string filePath);
private:
	
	//��ȡ�ļ�����
	int checkFileType();

	//�����ļ�������Ϣ
	bool initFileInf(std::string filePath);
	
	int _type;	// EFileType + EFileEncryptType << FILE_TYPE_MAX_LEN
	std::string _name;
	std::string _absolutePath;
	std::string _path;
	std::string _suffix;
};

typedef std::vector<CFile> SeqFile;
typedef std::pair<CFile, CFile> CFilePair;