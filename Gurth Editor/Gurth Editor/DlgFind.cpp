// DlgFind.cpp: 实现文件
//

#include "pch.h"
#include "Gurth Editor.h"
#include "DlgFind.h"
#include "afxdialogex.h"
#include "DlgMain.h"

// Global variable

DlgMain *pBack;

// DlgFind 对话框

IMPLEMENT_DYNAMIC(DlgFind, CDialogEx)

DlgFind::DlgFind(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIND, pParent)
{

}

DlgFind::~DlgFind()
{
}

void DlgFind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FIND, m_Edit_Find);
}


BEGIN_MESSAGE_MAP(DlgFind, CDialogEx)
	ON_BN_CLICKED(IDC_FINDNEXT, &DlgFind::OnBnClickedFindnext)
END_MESSAGE_MAP()


// DlgFind 消息处理程序

BOOL DlgFind::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pBack = (DlgMain*)pDlgMain;
	m_Edit_Find.SetWindowTextW(Find_Target);
	Find_Target.Empty();
	m_Edit_Find.SetFont(pBack->List.SystemSetting.FontList.Consolas12);
	GetDlgItem(IDC_STATIC)->SetFont(pBack->List.SystemSetting.FontList.MSShellDlg10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void DlgFind::OnBnClickedFindnext()
{
	// TODO: 在此添加控件通知处理程序代码
	CString CSBuffer;
	m_Edit_Find.GetWindowTextW(Find_Target);
	if (!Find_Target.IsEmpty())
	{
		int TargetLen = Find_Target.GetLength();
		pBack->m_Buffer.GetWindowTextW(CSBuffer);
		FindPos = CSBuffer.Find(Find_Target, FindPos);
		pBack->m_Buffer.SetFocus();
		if (FindPos == -1)
		{
			MessageBox(L"Cannot find \"" + Find_Target + L"\".", L"Tips", MB_OK | MB_ICONINFORMATION);
			FindPos = 0;
		}
		else
			pBack->m_Buffer.SetSel(FindPos, FindPos + TargetLen, FALSE);
		FindPos += TargetLen;
	}
	else
		MessageBox(L"Finding target Cannot be empty.", L"Warnning", MB_OK | MB_ICONWARNING);
}