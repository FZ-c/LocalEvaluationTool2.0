#pragma once
#include <string>
#include <vector>

#include "Core/JudgeManager/judge.h"
#include "Core/FileManager/project.h"

class CFunctionBase
{
public:
	CFunctionBase();
	virtual ~CFunctionBase() = default;

	static void setProject(CProject* project) { _project = project; }
	static void setJudgeManager(CJudgeManager* judge) { _judge = judge; }
	static CProject* getProject() { return _project; }
	static CJudgeManager* getJudgeManager() { return _judge; }

	const std::string& getFunctionName() const { return _functionName; }

	//����������� ��Ҫ�����κ�ʵ�ʶ��󣨳��˲�����
	virtual bool checkParams(std::vector<std::string> params);

	//ʵ�ʽ��ж����ĵط� �������������
	virtual bool runFuction();
protected:
	std::string _functionName;
	std::vector<std::string> _params;
private:
	static CProject* _project;
	static CJudgeManager* _judge;
};
