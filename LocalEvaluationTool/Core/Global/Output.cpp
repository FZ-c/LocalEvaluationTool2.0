#include "Output.h"

//�����Ϣ
void COutput::_OutputInf(std::string s, int ForeGroundColor/* = enmCFC_White*/, int BackGroundColor/* = enmCBC_Black*/) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, ForeGroundColor | BackGroundColor);
	std::cout << s;
	SetConsoleTextAttribute(handle, enmCFC_White | enmCBC_Black);
}

void COutput::OutputErrorMessage(std::string s) {
	_OutputInf("����: " + s, enmCFC_Red);
}


void COutput::OutputWarningMessage(std::string s) {
	_OutputInf("����: " + s, enmCFC_Yellow);
}


void COutput::OutputSuccessMessage(std::string s) {
	_OutputInf(s, enmCFC_Green);
}

void COutput::OutputMessage(std::string s) {
	_OutputInf("��ʾ: " + s);
}

void COutput::OutputFleshMessage(std::string s, int ForeGroundColor/* = enmCFC_White */ , int BackGroundColor/* = enmCBC_Black */ ) {
	_OutputInf("\r" + std::string(100, ' '));
	_OutputInf("\r" + s, ForeGroundColor, BackGroundColor);
}