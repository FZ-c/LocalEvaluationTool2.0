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

	//仅做参数检查 不要更改任何实际对象（除了参数）
	virtual bool checkParams(std::vector<std::string> params);

	//实际进行动作的地方 在这里操作对象
	virtual bool runFuction();
protected:
	std::string _functionName;
	std::vector<std::string> _params;
private:
	static CProject* _project;
	static CJudgeManager* _judge;
};
