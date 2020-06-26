#pragma once


// CTextDialog 對話方塊

class CTextDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDialog)

public:
	CTextDialog(CWnd* pParent = NULL);   // 標準建構函式
	virtual ~CTextDialog();

// 對話方塊資料
	enum { IDD = IDD_TEXT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	// Stores the text entered in the edit box
	CString m_TextString;
};
