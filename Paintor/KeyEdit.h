#pragma once
#include "afxwin.h"

const UINT WM_EDIT_ENTER = RegisterWindowMessage(_T("WM_EDIT_ENTER"));

class CKeyEdit :
	public CEdit
{
private:
	CFont m_myFont;
public:
	CKeyEdit();
	~CKeyEdit();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

