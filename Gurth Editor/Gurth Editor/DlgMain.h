#pragma once

#include "DataList.h"

// DlgMain 对话框

class DlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(DlgMain)

public:
	DlgMain(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DlgMain();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Buffer;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void AutoTab();
	BOOL SaveAS();
	DataList List;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveas();
	afx_msg void OnFileNewsession();
	afx_msg void OnFileExit();
	afx_msg void OnEditFind();
	afx_msg void OnEditReplace();
	afx_msg void OnToolsPreferance();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCut();
	afx_msg void OnEditClear();
	afx_msg void OnEditClearall();
	afx_msg void OnEnChangeBuffer();
	virtual void OnCancel();
	afx_msg void OnEditUndo();
};
