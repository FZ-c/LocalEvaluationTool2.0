#include "project.h"
#include "file.h"
#include "Core/Global/Output.h"

CProject::CProject(std::string path) :_path(path)
{
	if (path.empty())
	{
		_isActive = false;
		return;
	}
	if (_path.back() != '\\') _path.push_back('\\');
	_isActive = _scanFiles(_path);
	
	if(_dataFiles.empty() == false)
	{
		//ȥ��û�б�ƥ����ļ�
		for(std::map<std::string,CFilePair>::iterator it = _dataFiles.begin();it != _dataFiles.end();)
		{
			if(it->second.first.checkFileWork() == false || it->second.second.checkFileWork() == false)
			{
				std::map<std::string, CFilePair>::iterator tmpIt = it;
				++tmpIt;
				_dataFiles.erase(it);
				it = tmpIt;
			}
			else
			{
				++it;
			}
		}
		if(_dataFiles.empty())
		{
			COutput::OutputWarningMessage("·��" + path + "�²����������ļ���\n");
		}
	}
}

bool CProject::_scanFiles(std::string path, bool searchCodeFile/* = true*/, bool searchDataFile/* = true*/)
{
	if(checkDirExist(path) == false)
	{
		return false;
	}
	if (searchCodeFile) _codeFiles.clear();
	if (searchDataFile) _dataFiles.clear();

	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if (!(fileinfo.attrib & _A_SUBDIR)) {
				CFile newFile(path + fileinfo.name);
				if(newFile.checkFileWork())
				{
					if(newFile.checkFileHasType(EFileTypeCCodeFile) || newFile.checkFileHasType(EFileTypeCPPCodeFile))
					{
						//�����ļ�
						if(searchCodeFile)
						{
							_codeFiles.push_back(newFile);
						}
					}
					else
					{
						//�����������ļ�
						if(searchDataFile)
						{
							if (newFile.checkFileHasType(EFileTypeInputFile))
							{
								_dataFiles[newFile.getFileName()].first = newFile;
							}
							else
							{
								_dataFiles[newFile.getFileName()].second = newFile;
							}
						}
					}
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
	}

	//�����û���ļ���ɨ�赽
	if(_codeFiles.empty())
	{
		COutput::OutputWarningMessage("·��" + path + "�²����ڴ����ļ���\n");
	}
	if(_dataFiles.empty())
	{
		COutput::OutputWarningMessage("·��" + path + "�²����������ļ���\n");
	}
	
	return _codeFiles.empty() == false || _dataFiles.empty() == false;
}

bool CProject::checkDirExist(std::string dirName, bool printErr/* = false*/)
{
	struct stat buffer;
	if ((stat(dirName.c_str(), &buffer) != 0 || (buffer.st_mode & S_IFMT) != S_IFDIR))
	{
		if (printErr)
		{
			COutput::OutputErrorMessage("Ŀ¼ " + dirName + " ������!\n");
		}
		return false;
	}
	return true;
}

CFilePair CProject::getDataFilePair(std::string fileName)
{
	std::string pathTmp, name, suffixTmp;
	CFile::splitFileStr(fileName, pathTmp, name, suffixTmp);
	std::map<std::string, CFilePair>::iterator it = _dataFiles.find(name);
	if(it != _dataFiles.end())
	{
		return it->second;
	}
	return CFilePair();
}

bool CProject::checkDataFileActive(std::string fileName)
{
	std::string pathTmp, name, suffixTmp;
	CFile::splitFileStr(fileName, pathTmp, name, suffixTmp);
	return _dataFiles.find(name) != _dataFiles.end();
}

CFile CProject::getCodeFile(const std::string& fileName)
{
	for (SeqFile::iterator it = _codeFiles.begin(); it != _codeFiles.end(); ++it)
	{
		if(it->getFileCompleteName() == fileName)
		{
			return *it;
		}
	}
	return CFile();
}

void CProject::researchFiles(bool codeFile/* = false*/, bool dataFile/* = false*/)
{
	_scanFiles(_path, codeFile, dataFile);
}
