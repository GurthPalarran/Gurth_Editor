// RegistKey.cpp: 实现文件
//

#include "stdafx.h"
#include "Gurth Editor Launcher.h"
#include "RegistKey.h"
#include "afxdialogex.h"

//Extern variable

// RegistKey 对话框

IMPLEMENT_DYNAMIC(RegistKey, CDialogEx)

RegistKey::RegistKey(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_KEY, pParent)
{

}

RegistKey::~RegistKey()
{
}

void RegistKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_Edit_Key);
}


BEGIN_MESSAGE_MAP(RegistKey, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_KEY, &RegistKey::OnEnChangeEditKey)
	ON_BN_CLICKED(IDOK, &RegistKey::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RegistKey::OnBnClickedCancel)
END_MESSAGE_MAP()


// RegistKey 消息处理程序


BOOL RegistKey::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_Edit_Key.SetLimitText(29);
	CFont * SourceCodePro13 = new CFont;
	SourceCodePro13->CreatePointFont(130, L"Source Code Pro Semibold", NULL);
	m_Edit_Key.SetFont(SourceCodePro13);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL RegistKey::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (GetDlgItem(IDC_EDIT_KEY)->m_hWnd == pMsg->hwnd)
	{
		if (pMsg->message == WM_RBUTTONUP || pMsg->message == WM_KEYDOWN && pMsg->wParam == 'V' && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
			return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_BACK) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE ) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void RegistKey::OnEnChangeEditKey()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int Len;
	const int MAX_Len = 29;
	Len = m_Edit_Key.GetWindowTextLengthW();
	if (Len == 4 || Len == 9 || Len == 14 || Len == 19 || Len == 24)
	{
		m_Edit_Key.SetSel(Len, Len, TRUE);
		m_Edit_Key.ReplaceSel(L"-", FALSE);
	}

}


void RegistKey::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	Key_read.Empty();
	m_Edit_Key.GetWindowTextW(Key_read);
	CDialogEx::OnOK();
}


void RegistKey::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
