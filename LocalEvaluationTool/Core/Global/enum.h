#pragma once

/*
 * Debug��ʶ
 */
#define DEBUGMODE 0

/*
 * �ļ���������
 */
enum EFileEncryptType
{
	EFileEncryptTypeNormal		= 0x001,
	EFileEncryptTypeEncrypt		= 0x002,
	EFileEncryptTypeDecrypt		= 0x004,
};

/*
 * �����ļ�����
 */
#define FILE_TYPE_MAX_LEN 5
enum EFileType
{
	EFileTypeError			= 0x1,
	
	EFileTypeInputFile		= 0x2,
	EFileTypeOutputFile		= 0x4,
	
	EFileTypeCCodeFile		= 0x8,
	EFileTypeCPPCodeFile	= 0x10,
	
};

/*
 * �ļ���׺����
 */
#define FILE_SUFFIX_C					".c"
#define FILE_SUFFIX_CPP					".cpp"
#define FILE_SUFFIX_INPUTFILE			".in"
#define FILE_SUFFIX_OUTPUTFILE			".out"
#define FILE_SUFFIX_ENCRYPT_INPUTFILE	".encin"
#define FILE_SUFFIX_ENCRYPT_OUTPUTFILE	".encout"
#define FILE_SUFFIX_DECRYPT_INPUTFILE	".encin"
#define FILE_SUFFIX_DECRYPT_OUTPUTFILE	".encout"

/*
 * �������Ͷ���
 */
enum EJudgeType
{
	EJudgeNone		= 0x00, //Ĭ��״̬ ���ܽ�������
	EJudgeTypeACM	= 0x01,	//ACMģʽ �����ֹͣ
	EJudgeTypeOI	= 0x10,	//OIģʽ ȫ��
};