#pragma once

#ifndef _TYPE_DEFINE_
#define _TYPE_DEFINE_

typedef int GurthMod;
#define NOT_TRANS_CODE 0
#define INVERSE_TRANS_CODE 1

typedef unsigned int ErrorCode;
#define WITH_NO_ERROR 0
#define FILE_NOT_EXIST 1
#define ERROR_ARG 2

#endif // !_TYPE_DEFINE_

#ifndef _DATALIST_STRUCT_
#define _DATALIST_STRUCT_

struct fontlist
{
	CFont* CustomFont = new CFont;
	CFont* SourceCodePro12 = new CFont;
	CFont* Consolas12 = new CFont;
	CFont* MSShellDlg10 = new CFont;
};

typedef struct fontlist fontlist;

struct systemsetting
{
	fontlist FontList;
};

typedef struct systemsetting systemsetting;

#endif // !_DATALIST_STRUCT_


class DataList
{
public:
	DataList();
	~DataList();
	ErrorCode ArgParsing();
	void FileExist();

public:
	systemsetting SystemSetting;
	BOOL IsChanged = FALSE;
	BOOL IsFileExist = FALSE;
	CString Cmdline;
	CString FilePath;
	BOOL DoTransCode = TRUE;
	GurthMod TransCodeMod = INVERSE_TRANS_CODE;

private:
	CFont* PreFontSetting(CFont* NewFont);
};