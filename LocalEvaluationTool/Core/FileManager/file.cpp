#include "file.h"

#include "Core/Global/enum.h"
#include "Core/Global/Output.h"

CFile::CFile()
{
	_type = CUtil::calFileTypeValue(EFileTypeError);
}

CFile::CFile(std::string fileName)
{
	_type = CUtil::calFileTypeValue(EFileTypeError);
	initFileInf(fileName);
}

bool CFile::checkFileExist(std::string fileName, bool printErr/* = false*/) {
	struct stat buffer;
	if (stat(fileName.c_str(), &buffer) != 0 && printErr)
	{
		if (printErr)
		{
			COutput::OutputErrorMessage("文件 " + fileName + " 不存在!\n");
		}
		return false;
	}
	return true;
}

int CFile::checkFileType()
{
	return CUtil::instance()->getFileType(_suffix);
}

bool CFile::initFileInf(std::string filePath)
{
	//先转成绝对路径再处理
	filePath = CUtil::changePathAbsolute(filePath);
	if(checkFileExist(_absolutePath) == false)
	{
		return false;
	}
	_absolutePath = filePath;
	splitFileStr(_absolutePath, _path, _name, _suffix);

	_type = checkFileType();
	return checkFileWork() && _name.empty() == false;
}

bool CFile::checkFileHasType(int checkType) const 
{
	return (_type & checkType) == checkType;
}

bool CFile::isCodeFile() const
{
	return checkFileHasType(CUtil::calFileTypeValue(EFileTypeCCodeFile)) || checkFileHasType(CUtil::calFileTypeValue(EFileTypeCPPCodeFile));
}

bool CFile::isDataFile() const
{
	return checkFileHasType(CUtil::calFileTypeValue(EFileTypeInputFile)) || checkFileHasType(CUtil::calFileTypeValue(EFileTypeOutputFile));
}



void CFile::splitFileStr(std::string fileStr, std::string& filePath, std::string& fileName, std::string& fileSuffix)
{
	filePath.clear();
	fileName.clear();
	fileSuffix.clear();
	//把文件名和后缀取出来
	const size_t namePos = fileStr.find_last_of('\\');
	const size_t suffixPos = fileStr.find_last_of('.');
	int status = (namePos != std::string::npos) * 10 + (suffixPos != std::string::npos);
	switch(status)
	{
	case 0:
		{
			fileName = fileStr;
		}
		break;
	case 1:
		{
			fileSuffix = fileStr.substr(suffixPos);
			fileName = fileStr.substr(0, suffixPos);
		}
		break;
	case 10:
		{
			filePath = fileStr.substr(0, namePos + 1);
			fileName = fileStr.substr(namePos + 1);
		}
		break;
	case 11:
		{
			fileSuffix = fileStr.substr(suffixPos); 
			filePath = fileStr.substr(0, namePos + 1);
			fileName = fileStr.substr(namePos + 1, suffixPos - namePos - 1);
		}
	}
}

int CFile::getFileSize(std::string filePath)
{
	std::ifstream ifs(filePath);
	if (ifs.is_open() == false) return -1;
	ifs.seekg(0, std::ios::end);
	size_t size = static_cast<size_t>(ifs.tellg());
	ifs.close();
	return size;
}
