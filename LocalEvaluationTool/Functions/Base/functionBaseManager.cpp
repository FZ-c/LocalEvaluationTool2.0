#include "functionBaseManager.h"

CProject* CFunctionBase::_project = NULL;
CJudgeManager* CFunctionBase::_judge = NULL;

CFunctionBase::CFunctionBase()
{

}

bool CFunctionBase::checkParams(std::vector<std::string> params)
{
	return false;
}

bool CFunctionBase::runFuction()
{
	return false;
}