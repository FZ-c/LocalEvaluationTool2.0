#include "Output.h"

//输出信息
void COutput::_OutputInf(std::string s, int ForeGroundColor/* = enmCFC_White*/, int BackGroundColor/* = enmCBC_Black*/) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeGroundColor | BackGroundColor);
	std::cout << s;
	SetConsoleTextAttribute(handle, enmCFC_White | enmCBC_Black);
}

void COutput::OutputErrorMessage(std::string s) {
	_OutputInf("错误: " + s, enmCFC_Red);
}


void COutput::OutputWarningMessage(std::string s) {
	_OutputInf("警告: " + s, enmCFC_Yellow);
}


void COutput::OutputSuccessMessage(std::string s) {
	_OutputInf(s, enmCFC_Green);
}

void COutput::OutputMessage(std::string s) {
	_OutputInf("提示: " + s);
}

void COutput::OutputFleshMessage(std::string s, int ForeGroundColor/* = enmCFC_White */ , int BackGroundColor/* = enmCBC_Black */ ) {
	COORD info = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));
	_OutputInf("\r" + std::string(info.X - 1, ' '));
	_OutputInf("\r" + s, ForeGroundColor, BackGroundColor);
}