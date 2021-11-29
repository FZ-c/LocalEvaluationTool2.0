#pragma once

/*
 * Debug标识
 */
#define DEBUGMODE 0

/*
 * 文件加密类型
 */
enum EFileEncryptType
{
	EFileEncryptTypeNormal		= 0x001,
	EFileEncryptTypeEncrypt		= 0x002,
	EFileEncryptTypeDecrypt		= 0x004,
};

/*
 * 代码文件类型
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
 * 文件后缀定义
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
 * 判题类型定义
 */
enum EJudgeType
{
	EJudgeNone		= 0x00, //默认状态 不能进行评测
	EJudgeTypeACM	= 0x01,	//ACM模式 出错就停止
	EJudgeTypeOI	= 0x10,	//OI模式 全测
};