// DlgMain.cpp: 实现文件
//

#include "pch.h"
#include "Gurth Editor.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include "etc.h"

// DlgMain 对话框

IMPLEMENT_DYNAMIC(DlgMain, CDialogEx)

DlgMain::DlgMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINDLG, pParent)
{

}

DlgMain::~DlgMain()
{
}

void DlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUFFER, m_Buffer);
}


BEGIN_MESSAGE_MAP(DlgMain, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &DlgMain::OnBnClickedOk)
	ON_COMMAND(ID_FILE_NEW, &DlgMain::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &DlgMain::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &DlgMain::OnFileSave)
	ON_COMMAND(ID_FILE_SAVEAS, &DlgMain::OnFileSaveas)
	ON_COMMAND(ID_FILE_NEWSESSION, &DlgMain::OnFileNewsession)
	ON_COMMAND(ID_FILE_EXIT, &DlgMain::OnFileExit)
	ON_COMMAND(ID_EDIT_FIND, &DlgMain::OnEditFind)
	ON_COMMAND(ID_EDIT_REPLACE, &DlgMain::OnEditReplace)
	ON_COMMAND(ID_TOOLS_PREFERANCE, &DlgMain::OnToolsPreferance)
	ON_COMMAND(ID_EDIT_COPY, &DlgMain::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &DlgMain::OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, &DlgMain::OnEditCut)
	ON_COMMAND(ID_EDIT_CLEAR, &DlgMain::OnEditClear)
	ON_COMMAND(ID_EDIT_CLEARALL, &DlgMain::OnEditClearall)
	ON_EN_CHANGE(IDC_BUFFER, &DlgMain::OnEnChangeBuffer)
	ON_COMMAND(ID_EDIT_UNDO, &DlgMain::OnEditUndo)
END_MESSAGE_MAP()


// DlgMain 消息处理程序



BOOL DlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	ErrorCode ErrCode = List.ArgParsing();
	CString* Buffer = new CString;
	if (List.IsFileExist)
	{
		if (!TranscodingRead(Buffer, List.FilePath))
			MessageBox(L"Cannot open this file", L"Error", MB_OK | MB_ICONERROR);
	}
	else 
			MessageBox(L"Not such file:" + List.FilePath, L"Error", MB_OK | MB_ICONERROR);
	m_Buffer.SetWindowTextW(*Buffer);
	Buffer->Empty();

	m_Buffer.SetFocus();
	m_Buffer.SetFont(List.SystemSetting.FontList.CustomFont);

	m_Buffer.SetTabStops(8);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL DlgMain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		AutoTab();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_TAB)
	{
		m_Buffer.ReplaceSel(L"\t", FALSE);
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void DlgMain::AutoTab()
{
	wchar_t CSBuffer[256];
	memset(CSBuffer, 0, sizeof(CSBuffer));
	m_Buffer.GetLine(m_Buffer.LineFromChar(-1), CSBuffer, sizeof(CSBuffer));
	CString LastLine = CSBuffer;
	int n, m;
	m_Buffer.GetSel(n, m);
	m_Buffer.ReplaceSel(L"\r\n", TRUE);
	m += 2; n = m;
	m_Buffer.SetSel(n, m);
	int i = 0;
	CString CStmp;
	CStmp.Empty();
	do
	{
		CStmp = LastLine.Mid(i, 1);
		if (CStmp == L" ")
		{
			m_Buffer.ReplaceSel(L" ", FALSE);
			i++;
		}
		else if (CStmp == L"\t")
		{
			m_Buffer.ReplaceSel(L"\t", FALSE);
			i++;
		}
		else break;
	} while (true);

}

BOOL DlgMain::SaveAS()
{
	CString NewFilePath;
	NewFilePath.Empty();
	CFileDialog filedlg(
		FALSE,
		L".gurth",
		NULL,
		//OFN_ALLOWMULTISELECT |/* OFN_HIDEREADONLY |*/ OFN_FILEMUSTEXIST,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Gurth files(*.gurth)|*.gurth||",
		NULL);
	if (filedlg.DoModal())
	{
		NewFilePath = filedlg.GetPathName();
		CStdioFile GurthFile;
		CString CSBuffer;
		m_Buffer.GetWindowTextW(CSBuffer);
		if (TranscodingWrite(CSBuffer, NewFilePath))
			return TRUE;
		else return FALSE;
	}
	else return FALSE;
	return TRUE;
}


void DlgMain::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


void DlgMain::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (List.IsChanged)
	{
		UINT nSelect =
			MessageBox(L"Please remember save your data.\nClick YES to save it", L"Warning", MB_YESNO | MB_ICONWARNING);
		if (nSelect == IDYES) OnFileSave();
	}
	CDialogEx::OnOK();
}


void DlgMain::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	UINT nSelect =
		MessageBox(L"Please remember save your data.\nClick YES to save it", L"Warning", MB_YESNO | MB_ICONWARNING);
	if (nSelect == IDYES) OnFileSave();
	m_Buffer.SetWindowTextW(L"");
	List.IsFileExist = FALSE;
	List.IsChanged = FALSE;
}


void DlgMain::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	if (List.IsChanged)
	{
		UINT nSelect =
			MessageBox(L"Please remember save your data.\nClick YES to save it", L"Warning", MB_YESNO | MB_ICONWARNING);
		if (nSelect == IDYES) OnFileSave();
	}
	CString OpenFilePath;
	OpenFilePath.Empty();
	CFileDialog filedlg(
		TRUE,
		L".gurth",
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Gurth files(*.gurth)|*.gurth||",
		NULL);
	if (filedlg.DoModal() == IDOK)
	{
		OpenFilePath = filedlg.GetPathName();
		List.FilePath = OpenFilePath;
		List.FileExist();
		CString *CSBuffer = new CString;
		if (!List.IsFileExist || !TranscodingRead(CSBuffer, OpenFilePath))
				MessageBox(L"Cannot open this file", L"Error", MB_OK | MB_ICONERROR);
		m_Buffer.SetWindowTextW(*CSBuffer);
		CSBuffer->Empty();
	}
}


void DlgMain::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	if (List.IsFileExist)
	{
		CString CSBuffer;
		CSBuffer.Empty();
		m_Buffer.GetWindowTextW(CSBuffer);
		if (TranscodingWrite(CSBuffer, List.FilePath))
		{
			MessageBox(L"Successful saved.", L"Tips", MB_OK | MB_ICONINFORMATION);
			List.IsChanged = FALSE;
		}
	}
	else
	{
		if (SaveAS())
		{
			MessageBox(L"Successful saved.", L"Tips", MB_OK | MB_ICONINFORMATION);
			List.IsChanged = FALSE;
		}
	}
}


void DlgMain::OnFileSaveas()
{
	// TODO: 在此添加命令处理程序代码
	if (SaveAS())
	{
		MessageBox(L"Successful saved.", L"Tips", MB_OK | MB_ICONINFORMATION);
		List.IsChanged = FALSE;
	}
}


void DlgMain::OnFileNewsession()
{
	// TODO: 在此添加命令处理程序代码
}


void DlgMain::OnFileExit()
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx::OnCancel();
}


void DlgMain::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	m_Buffer.Undo();
}


void DlgMain::OnEditFind()
{
	AfxBeginThread(TreadFunFind, this, THREAD_PRIORITY_NORMAL, 0, 0);
}


void DlgMain::OnEditReplace()
{
	AfxBeginThread(TreadFunReplace, this, THREAD_PRIORITY_NORMAL, 0, 0);
}


void DlgMain::OnToolsPreferance()
{
	// TODO: 在此添加命令处理程序代码
	AfxBeginThread(TreadFunPreferance, this, THREAD_PRIORITY_NORMAL, 0, 0);
}


void DlgMain::OnEditCopy()
{
	// TODO: 在此添加命令处理程序代码;
	if (!List.IsChanged)
		List.IsChanged = TRUE;
	m_Buffer.Copy();
}


void DlgMain::OnEditPaste()
{
	// TODO: 在此添加命令处理程序代码
	if (!List.IsChanged)
		List.IsChanged = TRUE;
	m_Buffer.Paste();
}


void DlgMain::OnEditCut()
{
	// TODO: 在此添加命令处理程序代码
	if (!List.IsChanged)
		List.IsChanged = TRUE;
	m_Buffer.Cut();
}


void DlgMain::OnEditClear()
{
	// TODO: 在此添加命令处理程序代码
	if (!List.IsChanged)
		List.IsChanged = TRUE;
	m_Buffer.Clear();
}


void DlgMain::OnEditClearall()
{
	// TODO: 在此添加命令处理程序代码
	if (!List.IsChanged)
		List.IsChanged = TRUE;
	m_Buffer.SetWindowTextW(L"");
}


void DlgMain::OnEnChangeBuffer()
{
	if (!List.IsChanged)
	{
		List.IsChanged = TRUE;
	}
}


void DlgMain::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (List.IsChanged)
	{
		UINT nSelect =
			MessageBox(L"Please remember save your data.\nClick YES to save it", L"Warning", MB_YESNO | MB_ICONWARNING);
		if (nSelect == IDYES) OnFileSave();
	}
	CDialogEx::OnCancel();
}
