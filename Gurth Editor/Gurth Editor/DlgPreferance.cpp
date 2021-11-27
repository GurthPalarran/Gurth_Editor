// DlgPreferance.cpp: 实现文件
//

#include "pch.h"
#include "Gurth Editor.h"
#include "DlgPreferance.h"
#include "afxdialogex.h"
#include "DlgMain.h"

// DlgPreferance 对话框

IMPLEMENT_DYNAMIC(DlgPreferance, CDialogEx)

DlgPreferance::DlgPreferance(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PREFER, pParent)
{

}

DlgPreferance::~DlgPreferance()
{
}

void DlgPreferance::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_FONT, m_ButtonFont);
}


BEGIN_MESSAGE_MAP(DlgPreferance, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgPreferance::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &DlgPreferance::OnBnClickedButtonFont)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DlgPreferance 消息处理程序


BOOL DlgPreferance::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void DlgPreferance::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL DlgPreferance::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDialogEx::PreTranslateMessage(pMsg);
}


void DlgPreferance::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	DlgMain* pDM = (DlgMain*)pDlgMain;
	pDM->m_Buffer.SetFont(pDM->List.SystemSetting.FontList.CustomFont);
	CDialogEx::OnOK();
}


void DlgPreferance::OnBnClickedButtonFont()
{
	// TODO: 在此添加控件通知处理程序代码
	DlgMain* pDM = (DlgMain*)pDlgMain;
	LOGFONT lgFont;
	pDM->List.SystemSetting.FontList.CustomFont->GetLogFont(&lgFont);
	CFontDialog FontDlg(&lgFont,
		0
		| CF_INITTOLOGFONTSTRUCT           //表示第一个参数有效
		| CF_SCREENFONTS                   //屏幕字体
		| CF_PRINTERFONTS                  //可以打印的字体
		| CF_INACTIVEFONTS                 //隐藏的字体
		| CF_EFFECTS                       //字体效果
		| 0,
		NULL, this);
	if (IDOK == FontDlg.DoModal())
	{
		DlgMain* pDM = (DlgMain*)pDlgMain;
		if(pDM->List.SystemSetting.FontList.CustomFont->m_hObject)
			pDM->List.SystemSetting.FontList.CustomFont->DeleteObject();
		pDM->List.SystemSetting.FontList.CustomFont->CreateFontIndirectW(FontDlg.m_cf.lpLogFont);
		int a = 0;
	}
}

