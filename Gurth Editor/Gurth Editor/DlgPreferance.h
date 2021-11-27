#pragma once


// DlgPreferance 对话框

class DlgPreferance : public CDialogEx
{
	DECLARE_DYNAMIC(DlgPreferance)

public:
	DlgPreferance(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgPreferance();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PREFER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	LPVOID pDlgMain;
	afx_msg void OnBnClickedOk();
	CButton m_ButtonFont;
	afx_msg void OnBnClickedButtonFont();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
