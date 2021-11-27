#pragma once


// DlgFind 对话框

class DlgFind : public CDialogEx
{
	DECLARE_DYNAMIC(DlgFind)

public:
	DlgFind(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgFind();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFindnext();
public:
	LPVOID pDlgMain;
	int FindPos = 0;
	virtual BOOL OnInitDialog();
	CEdit m_Edit_Find;
	CString Find_Target;
};
