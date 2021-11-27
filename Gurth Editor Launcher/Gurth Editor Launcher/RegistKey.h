#pragma once


// RegistKey 对话框

class RegistKey : public CDialogEx
{
	DECLARE_DYNAMIC(RegistKey)

public:
	RegistKey(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RegistKey();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_KEY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CEdit m_Edit_Key;
	CString Key_read;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEnChangeEditKey();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
