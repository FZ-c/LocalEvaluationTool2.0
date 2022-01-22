#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "Core/Global/util.h"

/*
 * 文件管理类
 */
class CFile
{
public:
	CFile(const std::string& fileName);
	CFile();
	~CFile() = default;

	//检查文件是否存在
	static bool checkFileExist(std::string fileName, bool printErr = false);
	
	const std::string& getFileName() const { return _name; }
	std::string getFileCompleteName() const { return _name + _suffix; }
	const std::string& getAbsolutePath() const { return _absolutePath; }
	const std::string& getPath() const { return _path; }
	const int& getFileType() const { return _type; }

	//检查文件是否有某类型
	bool checkFileHasType(int checkType) const;

	//检查文件是否正常
	bool checkFileWork() const { return checkFileHasType(CUtil::calFileTypeValue(EFileTypeError)) == false; }

	//检查文件是否为代码文件
	bool isCodeFile() const;

	//检查文件是否为数据文件
	bool isDataFile() const;

	//分割文件名部分
	static void splitFileStr(std::string fileStr, std::string& filePath, std::string& fileName, std::string& fileSuffix);

	//获取文件大小
	static int getFileSize(std::string filePath);
private:
	
	//获取文件类型
	int checkFileType();

	//解析文件基本信息
	bool initFileInf(std::string filePath);
	
	int _type;	// EFileType + EFileEncryptType << FILE_TYPE_MAX_LEN
	std::string _name;
	std::string _absolutePath;
	std::string _path;
	std::string _suffix;
};

typedef std::vector<CFile> SeqFile;
typedef std::pair<CFile, CFile> CFilePair;