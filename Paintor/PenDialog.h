#pragma once


// CPenDialog 對話方塊

class CPenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenDialog)

public:
	CPenDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CPenDialog();

// 對話方塊資料
	enum { IDD = IDD_PENWIDTH_DLG };

	int m_PenWidth;           // Record the current pen width

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPenwidth0();
	afx_msg void OnPenwidth1();
	afx_msg void OnPenwidth2();
	afx_msg void OnPenwidth3();
	afx_msg void OnPenwidth4();
	afx_msg void OnPenwidth5();
};
