#pragma once


// CTextDialog ��ܤ��

class CTextDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTextDialog)

public:
	CTextDialog(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~CTextDialog();

// ��ܤ�����
	enum { IDD = IDD_TEXT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	// Stores the text entered in the edit box
	CString m_TextString;
};
