// DlgReplace.cpp: 实现文件
//

#include "pch.h"
#include "Gurth Editor.h"
#include "DlgReplace.h"
#include "afxdialogex.h"
#include "DlgMain.h"


// Global variable

DlgMain *pBackRe;

// DlgReplace 对话框

IMPLEMENT_DYNAMIC(DlgReplace, CDialogEx)

DlgReplace::DlgReplace(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REPLACE, pParent)
{

}

DlgReplace::~DlgReplace()
{
}

void DlgReplace::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REPLACE, m_Replace_Next);
	DDX_Control(pDX, IDC_REPLACE_ALL, m_Replace_All);
	DDX_Control(pDX, IDC_EDIT_TARGET, m_Target);
	DDX_Control(pDX, IDC_EDIT_REPLACE, m_Replace);
}


BEGIN_MESSAGE_MAP(DlgReplace, CDialogEx)
	ON_BN_CLICKED(IDC_REPLACE, &DlgReplace::OnBnClickedReplace)
	ON_BN_CLICKED(IDC_REPLACE_ALL, &DlgReplace::OnBnClickedReplaceAll)
END_MESSAGE_MAP()


// DlgReplace 消息处理程序


BOOL DlgReplace::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	pBackRe = (DlgMain*)pDlgMain;
	m_Target.SetWindowTextW(ReplaceTarget);
	m_Target.SetFont(pBackRe->List.SystemSetting.FontList.Consolas12);
	m_Replace.SetFont(pBackRe->List.SystemSetting.FontList.Consolas12);
	//GetDlgItem(IDC_STATIC)->SetFont(pBackRe->List.SystemSetting.FontList.MSShellDlg10);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgReplace::OnBnClickedReplace()
{
	// TODO: 在此添加控件通知处理程序代码

	m_Target.GetWindowTextW(ReplaceTarget);
	if (!ReplaceTarget.IsEmpty())
	{
		m_Replace.GetWindowTextW(ReplaceWith);
		CString CSBuffer;
		int TargetLen = ReplaceTarget.GetLength();
		int ReplaceLen = ReplaceWith.GetLength();
		pBackRe->m_Buffer.GetWindowTextW(CSBuffer);
		//ReplacePos = CSBuffer.Replace(ReplaceTarget, ReplaceWith);
		ReplacePos = CSBuffer.Find(ReplaceTarget, ReplacePos);
		pBackRe->m_Buffer.SetFocus();
		if (ReplacePos == -1)
		{
			MessageBox(L"Cannot find \"" + ReplaceTarget + L"\".", L"Tips", MB_OK | MB_ICONINFORMATION);
			ReplacePos = 0;
		}
		else
		{
			pBackRe->m_Buffer.SetFocus();
			pBackRe->m_Buffer.SetSel(ReplacePos, ReplacePos + TargetLen, FALSE);
			CSBuffer.Delete(ReplacePos, TargetLen);
			CSBuffer.Insert(ReplacePos, ReplaceWith);
			pBackRe->m_Buffer.SetWindowTextW(CSBuffer);
			pBackRe->m_Buffer.SetSel(ReplacePos, ReplacePos + ReplaceLen, FALSE);
			ReplacePos += TargetLen;
			pBackRe->List.IsChanged = TRUE;
		}
		CSBuffer.Empty();
	}
	else
		MessageBox(L"Replace target cannot be empty.", L"Warnning", MB_OK | MB_ICONWARNING);
}


void DlgReplace::OnBnClickedReplaceAll()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ReplaceTarget;
	CString ReplaceWith;
	m_Target.GetWindowTextW(ReplaceTarget);
	if (!ReplaceTarget.IsEmpty())
	{
		m_Replace.GetWindowTextW(ReplaceWith);
		CString CSBuffer;
		pBackRe->m_Buffer.GetWindowTextW(CSBuffer);
		int ReplaceNumb = CSBuffer.Replace(ReplaceTarget, ReplaceWith);
		if (ReplaceNumb > 0)
		{
			CString Mssg;
			Mssg.Format(L"%d \"%s\" replaced.", ReplaceNumb, ReplaceTarget);
			MessageBox(Mssg, L"Tips", MB_OK | MB_ICONWARNING);
			pBackRe->List.IsChanged = TRUE;
		}
		else
			MessageBox(L"No target will replace.", L"Warnning", MB_OK | MB_ICONWARNING);
		pBackRe->m_Buffer.SetWindowTextW(CSBuffer);
		CSBuffer.Empty();
	}
	else
		MessageBox(L"Replace target cannot be empty.", L"Warnning", MB_OK | MB_ICONWARNING);

}
