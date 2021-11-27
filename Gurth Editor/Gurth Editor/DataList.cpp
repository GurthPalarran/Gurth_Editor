#include "pch.h"
#include "DataList.h"

DataList::DataList()
{
	SystemSetting.FontList.SourceCodePro12->CreatePointFont(120, L"Source Code Pro Semibold", NULL);
	SystemSetting.FontList.Consolas12->CreatePointFont(120, L"Consolas", NULL);
	SystemSetting.FontList.MSShellDlg10->CreatePointFont(100, L"MS Shell Dlg", NULL);
	SystemSetting.FontList.CustomFont = PreFontSetting(SystemSetting.FontList.CustomFont);
}

DataList::~DataList()
{
}

ErrorCode DataList::ArgParsing()
{
	FilePath.Empty();
	if (Cmdline.IsEmpty()) return TRUE;
	CString CStmp;
	BOOL ShowQuot = FALSE;
	int CmdLen = Cmdline.GetLength();
	for (int i = 0; i < CmdLen; i++)
	{
		CStmp.Empty();
		if (Cmdline.Mid(i, 1) == L"\"" && !ShowQuot)
		{
			i++;
			ShowQuot = TRUE;
			CString CSBuffer;
			do
			{
				if (i >= CmdLen) break;
				CSBuffer.Empty();
				CSBuffer = Cmdline.Mid(i, 1);
				if (CSBuffer == L"\"") break;
				FilePath += CSBuffer;
				i++;
			} while (TRUE);
			FileExist();
		}
		else if (Cmdline.Mid(i, 1) == L"-")
		{
			i++;
			CString ACSBuffer;
			if (Cmdline.Mid(i, 1) == L" ") return ERROR_ARG;
			do
			{	
				if (i >= CmdLen) break;
				ACSBuffer.Empty();
				ACSBuffer = Cmdline.Mid(i, 1);
				if (ACSBuffer == L" ") break;
				else if (ACSBuffer == L"d")
					TransCodeMod = NOT_TRANS_CODE;
				else return ERROR_ARG;
				i++;
			} while (TRUE);				
		}
	}
	return WITH_NO_ERROR;
}

void DataList::FileExist()
{
	DWORD dwAttrib = GetFileAttributes(FilePath);
	if (!(INVALID_FILE_ATTRIBUTES != dwAttrib && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) == 0))
	{
		if (FilePath.IsEmpty())
		{
			MessageBox(NULL, L"No such file.", L"Warnnig", MB_OK);
			IsFileExist = FALSE;
		}
	}
	else IsFileExist = TRUE;
}

CFont* DataList::PreFontSetting(CFont* NewFont)
{
#ifdef _PRIMARY_
	LOGFONT logfont = {0};
	lstrcpy(logfont.lfFaceName, L"Source Code Pro");
	logfont.lfWeight = 600;
	logfont.lfWidth = 0;
	logfont.lfHeight = -22;
	logfont.lfEscapement = 0;
	logfont.lfUnderline = FALSE;
	logfont.lfItalic = FALSE;
	logfont.lfStrikeOut = FALSE;
	logfont.lfCharSet = UNICODE;	
	NewFont->CreateFontIndirectW(&logfont);
#endif // _PRIMARY_

	return NewFont;
}
