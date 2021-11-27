#include "pch.h"
#include "etc.h"
#include "DlgMain.h"
#include "DlgFind.h"
#include "DlgReplace.h"
#include "DlgPreferance.h"


BOOL TranscodingRead(CString *Content, CString FileName)
{
	CStdioFile GurthFile;
	if (GurthFile.Open(FileName, CFile::typeBinary | CFile::modeRead | CFile::shareDenyWrite))
	{
		ULONGLONG filelen = GurthFile.GetLength();
		BYTE codeRead, codeOut;
		char *pc = new char[2];
		pc[1] = '\0';
		(*Content).Empty();
		USES_CONVERSION;
		for (ULONGLONG i = 0; i < filelen; i++)
		{
			GurthFile.Read(&codeRead, 1);
			codeOut = ~codeRead;
			*pc = (char)codeOut;
			(*Content).Append(A2T(pc));
		}
		GurthFile.Close();
		return TRUE;
	}
	else return FALSE;
}


BOOL TranscodingWrite(CString Content, CString FileName)
{
	CStdioFile GurthFile;
	if (GurthFile.Open(FileName, CFile::modeCreate | CFile::typeBinary | CFile::modeWrite | CFile::shareDenyWrite))
	{
		ULONGLONG BufferLen = Content.GetLength();
		BYTE codeRead, codeOut;
		USES_CONVERSION;
		char *pc = new char[2];
		pc[1] = '\0';
		for (int i = 0; i < BufferLen; i++)
		{
			pc = T2A(Content.Mid(i, 1));
			codeRead = (BYTE)(*pc);
			codeOut = ~codeRead;
			GurthFile.Write(&codeOut, 1);
		}
		GurthFile.Close();
		return TRUE;
	}
	else return FALSE;
}

BOOL DirectRead(CString* Content, CString FileName)
{
	CStdioFile GurthFile;
	CString CStmp;
	CStmp.Empty();
	Content->Empty();
	if (GurthFile.Open(FileName, CFile::typeText | CFile::modeRead | CFile::shareDenyWrite))
	{
		do
		{
			GurthFile.ReadString(CStmp);
			if (CStmp.IsEmpty()) break;
			(*Content) += CStmp;
			(*Content) += L"/n/r";
		} while (TRUE);
	}
	return TRUE;
}

BOOL WriteGpConfig(CString gpconfigPath)
{
	return TRUE;
}


BOOL ReadGpConfig(CString gpconfigPath)
{
	return TRUE;
}

BOOL UserOperation::getuseroperation(CString cmdline)
{
	return TRUE;
}

UINT TreadFunFind(LPVOID pParam)
{
	DlgFind Dlgfind;
	Dlgfind.pDlgMain = pParam;
	DlgMain* pG = (DlgMain*)pParam;
	int nStart, nEnd;
	pG->m_Buffer.GetSel(nStart, nEnd);
	CString CSBuffer;
	pG->m_Buffer.GetWindowTextW(CSBuffer);
	Dlgfind.Find_Target = CSBuffer.Mid(nStart, nEnd - nStart);
	CSBuffer.Empty();
	Dlgfind.DoModal();
	return 0;
}

UINT TreadFunReplace(LPVOID pParam)
{
	DlgReplace Dlgreplace;
	Dlgreplace.pDlgMain = pParam;
	DlgMain* pG = (DlgMain*)pParam;
	int nStart, nEnd;
	pG->m_Buffer.GetSel(nStart, nEnd);
	CString CSBuffer;
	pG->m_Buffer.GetWindowTextW(CSBuffer);
	Dlgreplace.ReplaceTarget = CSBuffer.Mid(nStart, nEnd - nStart);
	CSBuffer.Empty();
	Dlgreplace.DoModal();
	return 0;
}

UINT TreadFunPreferance(LPVOID pParam)
{
	DlgPreferance Dlgpreferance;
	Dlgpreferance.pDlgMain = pParam;
	//DlgMain* pG = (DlgMain*)pParam;
	Dlgpreferance.DoModal();
	return 0;
}
