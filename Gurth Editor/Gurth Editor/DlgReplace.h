#pragma once


// DlgReplace 对话框

class DlgReplace : public CDialogEx
{
	DECLARE_DYNAMIC(DlgReplace)

public:
	DlgReplace(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgReplace();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REPLACE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedReplace();
	afx_msg void OnBnClickedReplaceAll();
	CButton m_Replace_Next;
	CButton m_Replace_All;
	CEdit m_Target;
	CEdit m_Replace;
	LPVOID pDlgMain;
	int ReplacePos = 0;
	CString ReplaceTarget;
	CString ReplaceWith;
};
