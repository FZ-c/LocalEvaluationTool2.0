#pragma once

#include <iostream>
#include <string>
#include <Windows.h>

class COutput
{
public:
	//ǰ��ɫ
	enum ConsoleForegroundColor
	{
		enmCFC_Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		enmCFC_Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		enmCFC_Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		enmCFC_Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		enmCFC_Purple = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		enmCFC_Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		enmCFC_Gray = FOREGROUND_INTENSITY,
		enmCFC_White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		enmCFC_HighWhite = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		enmCFC_Black = 0,
	};

	//��ɫ
	enum ConsoleBackGroundColor
	{
		enmCBC_Red = BACKGROUND_INTENSITY | BACKGROUND_RED,
		enmCBC_Green = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		enmCBC_Blue = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		enmCBC_Yellow = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		enmCBC_Purple = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		enmCBC_Cyan = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		enmCBC_White = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		enmCBC_HighWhite = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		enmCBC_Black = 0,
	};


	//�����Ϣ
	static void _OutputInf(const std::string& s, int ForeGroundColor = enmCFC_White, int BackGroundColor = enmCBC_Black);

	//���������Ϣ
	static void OutputErrorMessage(const std::string& s);

	//���������Ϣ
	static void OutputWarningMessage(const std::string& s);

	//����ɹ���Ϣ
	static void OutputSuccessMessage(const std::string& s);

	//�����ʾ��Ϣ
	static void OutputMessage(const std::string& s);

	//���ˢ����Ϣ
	static void OutputFleshMessage(const std::string& s, int ForeGroundColor = enmCFC_White, int BackGroundColor = enmCBC_Black);
};

